/**
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of and a contribution to the lwIP TCP/IP stack.
 *
 * Credits go to Adam Dunkels (and the current maintainers) of this software.
 *
 * Christiaan Simons rewrote this file to get a more stable echo application.
 *
 **/

 /* This file was modified by ST */
#include "main.h"
#include "tcp_echoserver.h"

#include "svCLI.h"
#include "svDebug.h"
#include "LED.h"

#if LWIP_TCP
static struct tcp_pcb *tcp_echoserver_pcb;


/* callback functions */
static err_t app_callback_accepted(void *arg, struct tcp_pcb *pcb_new, err_t err);
static err_t app_callback_received(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void app_callback_error(void *arg, err_t err);
static err_t app_callback_poll(void *arg, struct tcp_pcb *tpcb);
static err_t app_callback_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);

/* functions */
static void app_send_data(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es); //send function
static void app_close_connection(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es); //close function

/**
  * @brief  Initializes the tcp echo server
  * @param  None
  * @retval None
  */
err_t app_echoserver_init(void)
{
  /* create new tcp pcb */
  err_t err;
  tcp_echoserver_pcb = tcp_new();

  if (tcp_echoserver_pcb == NULL)
  {
    //lack of memory
    memp_free(MEMP_TCP_PCB, tcp_echoserver_pcb);
    return ERR_MEM;
  }
  /* bind echo_pcb to port 7 (ECHO protocol) */
  err = tcp_bind(tcp_echoserver_pcb, IP_ADDR_ANY, 7);

  if (err != ERR_OK)
  {
    /* deallocate the pcb */
    /* Failt to bind */
    memp_free(MEMP_TCP_PCB, tcp_echoserver_pcb);
    return err;
  }

  /* start tcp listening for echo_pcb */
  tcp_echoserver_pcb = tcp_listen(tcp_echoserver_pcb);

  /* initialize LwIP tcp_accept callback function */
  tcp_accept(tcp_echoserver_pcb, app_callback_accepted); // regi accept callback

  return ERR_OK;
}

/**
  * @brief  This function is the implementation of tcp_accept LwIP callback
  * @param  arg: not used
  * @param  newpcb: pointer on tcp_pcb struct for the newly created tcp connection
  * @param  err: not used 
  * @retval err_t: error status
  */
/* accept callback */
static err_t app_callback_accepted(void *arg, struct tcp_pcb *pcb_new, err_t err)
{
  struct tcp_echoserver_struct *es;

  LWIP_UNUSED_ARG(arg); //remove warning
  LWIP_UNUSED_ARG(err);

  tcp_setprio(pcb_new, TCP_PRIO_NORMAL); //set priority for new pcb  (TCP_PRIO_MIN , TCP_PRIO_NORMAL)

  es = (struct tcp_echoserver_struct*)
  mem_malloc(sizeof(struct tcp_echoserver_struct)); //allocate tcp_echoserver_struct

  if (es == NULL) //lack of memory
  {
    app_close_connection(pcb_new, es); //close connection
    return ERR_MEM;
  }

  es->state = ES_ACCEPTED; //accepted
  es->pcb = pcb_new; //set pcb pointer
  es->retries = 0; //clear counter
  es->p = NULL; //clear buffer pointer

  tcp_arg(pcb_new, es);   //send es structure as an argument
  tcp_recv(pcb_new, app_callback_received); //register receive callback
  tcp_err(pcb_new, app_callback_error); //register error callback
  tcp_poll(pcb_new, app_callback_poll, 0); //register poll callback

  return ERR_OK;
}


/**
  * @brief  This function is the implementation for tcp_recv LwIP callback
  * @param  arg: pointer on a argument for the tcp_pcb connection
  * @param  tpcb: pointer on the tcp_pcb connection
  * @param  pbuf: pointer on the received pbuf
  * @param  err: error information regarding the reveived pbuf
  * @retval err_t: error code
  */
/* receive callback */
static err_t app_callback_received(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  struct tcp_echoserver_struct *es;
  err_t ret_err;

  LWIP_ASSERT("arg != NULL", arg != NULL); //check argument
  es = (struct tcp_echoserver_struct*) arg;

  if (p == NULL) //callback is called but there's no data
  {
    es->state = ES_CLOSING;
    if (es->p == NULL)
    {
      app_close_connection(tpcb, es); //close connection
    }
    else //if there's remained data to send
    {
      tcp_sent(tpcb, app_callback_sent); //register send callback
      app_send_data(tpcb, es); //send remained data
    }
    ret_err = ERR_OK;
  }
  else if (err != ERR_OK) //error when receiving
  {
    if (p != NULL) //buffer is not empty
    {
      es->p = NULL;
      pbuf_free(p); //clear buffer
    }
    ret_err = err;
  }
  else if (es->state == ES_ACCEPTED) //first data receiving
  {
    es->state = ES_RECEIVED; //change state
    es->p = p; //set buffer pointer
    tcp_sent(tpcb, app_callback_sent); //register send callback
    app_send_data(tpcb, es); //send data via es->p
    ret_err = ERR_OK;
  }
  else if (es->state == ES_RECEIVED) //additional data receiving
  {
    if (es->p == NULL) //no data to send
    {
      es->p = p; //set buffer pointer
      app_send_data(tpcb, es); //send data
    }
    else //buffer is not empty, there's data to send
    {
      struct pbuf *ptr = es->p; //head buffer
      pbuf_chain(ptr, p); //append tail buffer to the head, this buffer will be handled by poll callback
    }
    ret_err = ERR_OK;
  }
  else if (es->state == ES_CLOSING) //receiving data when connection is closing
  {
    tcp_recved(tpcb, p->tot_len); //advertise window size
    es->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  else //receive complete
  {
    tcp_recved(tpcb, p->tot_len); //advertise window size
    es->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}

/**
  * @brief  This function implements the tcp_err callback function (called
  *         when a fatal tcp_connection error occurs. 
  * @param  arg: pointer on argument parameter 
  * @param  err: not used
  * @retval None
  */
/* error callback */
static void app_callback_error(void *arg, err_t err)
{
  struct tcp_echoserver_struct *es;
  LWIP_UNUSED_ARG(err);

  es = (struct tcp_echoserver_struct*) arg;
  if (es != NULL)
  {
    mem_free(es); //free es structure
  }

  HAL_GPIO_WritePin(LED3_RED_GPIO_Port, LED3_RED_Pin, GPIO_PIN_SET); //turn on RED LED when there's error.
}

/**
  * @brief  This function implements the tcp_poll LwIP callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: pointer on the tcp_pcb for the current tcp connection
  * @retval err_t: error code
  */
/* poll callback */
static err_t app_callback_poll(void *arg, struct tcp_pcb *tpcb)
{
  struct tcp_echoserver_struct *es;
  es = (struct tcp_echoserver_struct*) arg;

  if (es == NULL) //if there's no es structure
  {
    tcp_abort(tpcb); //abort connection
    return ERR_ABRT;
  }

  if (es->p != NULL) //if there's data to send
  {
    tcp_sent(tpcb, app_callback_sent); //register send callback
    app_send_data(tpcb, es); //send data
  }
  else //no data to send
  {
    if (es->state == ES_CLOSING)
    {
      app_close_connection(tpcb, es);   //close connection
    }
  }

  return ERR_OK;
}

/**
  * @brief  This function implements the tcp_sent LwIP callback (called when ACK
  *         is received from remote host for sent data) 
  * @param  None
  * @retval None
  */
/* send callback */
static err_t app_callback_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct tcp_echoserver_struct *es;
  LWIP_UNUSED_ARG(len);

  es = (struct tcp_echoserver_struct*) arg;
  es->retries = 0;

  if (es->p != NULL) //if there's data to send
  {
    tcp_sent(tpcb, app_callback_sent); //register send callback
    app_send_data(tpcb, es); //send data
  }
  else //no data to send
  {
    if (es->state == ES_CLOSING)
    {
      app_close_connection(tpcb, es); //close connection
    }
  }
  return ERR_OK;
}


/**
  * @brief  This function is used to send data for tcp connection
  * @param  tpcb: pointer on the tcp_pcb connection
  * @param  es: pointer on echo_state structure
  * @retval None
  */
/* send data */
static void app_send_data(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;

  // while no error, data to send, data size is smaller than the size of the send buffer
  while ((wr_err == ERR_OK) && (es->p != NULL)
      && (es->p->len <= tcp_sndbuf(tpcb)))
  {
    ptr = es->p;
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, TCP_WRITE_FLAG_COPY); //send data

    if (wr_err == ERR_OK)
    {
      u16_t plen;
      u8_t freed;

      plen = ptr->len;
      es->p = ptr->next;

      if (es->p != NULL) //there's chained buffer to send
      {
        pbuf_ref(es->p);  //increase reference counter
      }

      do
      {
        freed = pbuf_free(ptr);   //free old buffer
      }
      while (freed == 0);

      tcp_recved(tpcb, plen);     //advertise window size
    }
    else
    {
      es->p = ptr;  //fail to send, recover buffer pointer
      es->retries++;  //increase counter
    }
  }
}

/**
  * @brief  This functions closes the tcp connection
  * @param  tcp_pcb: pointer on the tcp connection
  * @param  es: pointer on echo_state structure
  * @retval None
  */
/* close connection */
static void app_close_connection(struct tcp_pcb *tpcb, struct tcp_echoserver_struct *es)
{
  /* clear callback functions */
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  if (es != NULL)
  {
    mem_free(es);   //free es structure
  }

  tcp_close(tpcb);    //close connection
}

#endif
