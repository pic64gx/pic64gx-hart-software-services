/*******************************************************************************
 * Copyright 2021 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Bare metal driver for the Coreplex Inter Hart Communication (IHC) subsystem
 *
 */
/*=========================================================================*//**

  ==============================================================================
  Introduction
  ==============================================================================
  The Bare metal Coreplex-IHC driver facilitates the use of the Coreplex IHC
  subsystem which allows inter hart/processor communication as part of a
  HW/SW stack.

  ==============================================================================
  Definition of terms
  ==============================================================================
  Terms definition

     - Channel A-B
       This refers to the communications connection between any two Harts or
       contexts. ( Note: A Context refers to a collection of harts.)
     - Coreplex Inter Hart Communication Channel (IHCC)
       This is the IP core for each channel. It has an A and a B side. Each
       side is configured from the hart associated with each side using the apb
       bus.
     - Coreplex Inter Hart Communication Interrupt Aggregator (IHCIA) IP
       This is the Interrupt Aggregator Core, one for each hart. It takes inputs
       from the Coreplex IHCC's and generates an interrupt to the connected hart
       based on the programmed configuration.
     - Coreplex Inter Hart Communication (IHC) subsystem
       This is the collection of Coreplex IHCC's and Coreplex IHCIA's which form the
       Inter hart Communications subsystem.

  ==============================================================================
  Hardware Flow Dependencies
  ==============================================================================
  Below is a simplified view of the Coreplex IHC subsytem.

  ```
        ^               ^               ^               ^               ^
        |               |               |               |               |
+-----------------------------------------------------------------------------------------+
|       | Int to hart0  | Int to hart1  | Int to hart2  | Int to hart3  | Int to hart4    |
|       |               |               |               |               |                 |
|    +--+--------+   +--+--------+   +--+--------+   +--+--------+   +--+--------+        |
|    | MiV IHCIA |   | MiV IHCIA |   | MiV IHCIA |   | MiV IHCIA |   | MiV IHCIA |        |
|    |  hart0    |   |  hart1    |   |  hart2    |   |  hart3    |   |  hart4    |        |
|    +---+-------+   +^--^-------+   +^--^---^---+   +--------^--+   +---^-^---^-+        |
|        ^            |  |            |  |   |                |          | |   |          |
|        |   +--------+  |  +---------+  |   |                |          | |   |          |
|        |   |           |  |       +----+   |                |          | |   |          |
|      +-+---+-+      +--+--+-+     |  +-----+-+       +------++         | |   |          |
|      |  IHCC |      | IHCC  |     |  | IHCC  |       | IHCC  +---------+ |   |          |
|      | 0<->1 |      | 1<->2 |     |  | 2<->4 +----+  | 3<->4 |           |   |          |
|      +-------+      +-------+     |  +-------+    |  +-------+           |   |          |
|                                   |               +----------------------+   |          |
|      +-------+      +-------+     |  +-------+                               |          |
|      | IHCC  |      | IHCC  |     +--+ IHCC  +-------------------------------+          |
|      | 0<->2 |      | 1<->3 |        | 2<->4 |                                          |
|      +-------+      +-------+        +-------+                                          |
|                                                                                         |
|      +-------+      +-------+       Coreplex IHC - Inter Hart Communication subsytem    |
|      | IHCC  |      | IHCC  |       Not all connections are shown for                   |
|      | 0<->3 |      | 1<->4 |       reasons of clarity                                  |
|      +-------+      +-------+                                                           |
|                                                                                         |
|      +-------+                                                                          |
|      | IHCC  |                                                                          |
|      | 0<->4 |                                                                          |
|      +-------+                                                                          |
|                                                                                         |
+-----------------------------------------------------------------------------------------+


  ```

  ==============================================================================
  Theory of Operation
  ==============================================================================
  The Coreplex IHC subsystem facilitates sending messages between independent
  software contexts in an AMP system. API functions are provided for the
  following:
    - Initialization and configuration functions
    - Polled transmit and receive functions
    - Interrupt driven transmit and receive functions

  --------------------------------
  Initialization and Configuration
  --------------------------------
  At start-up, one hart should be designated to initialize the Coreplex IHC and set
  the default values.
  This hart must have access to the full memory range. In the Microchip software
  ecosystem, the HSS, running on E51 monitor core carries out this function.
  Local contexts initialize local channels. Examples of initialization are given
  in the functions descriptions.
  A drawing of an example start-up showing the order of the functions used is
  shown below:

```
    +----------------+
    |                |
    |  monitor hart  |                           Example start-up
    |                |
    +-------+--------+
            |
   +--------v---------+
   |IHC_global_init()|
   +--------+---------+
            |
+-----------v--------------+   +----------------+---------------------------------+--------------------------------+---------------------------------+
|IHC_local_context_init()  |   |                |                                 |                                |                                 |
+-----------+--------------+   |                |                                 |                                |                                 |
            ^                  |                |                                 |                                |                                 |
+-----------+--------------+   |    +-----------v--------------+    +-------------v------------+     +-------------v------------+     +--------------v-----------+
|IHC_local_remote_config() |   |    |IHC_local_context_init() |    |IHC_local_context_init() |     |IHC_local_context_init() |     |IHC_local_context_init() |
| channel 0 <> 1 config    |   |    +--------------------------+    +-------------+------------+     +-------------+------------+     +--------------+-----------+
+--------------------------+   |                                                  |                                |                                 |
            |                  |    +--------------------------+    +-------------v------------+     +-------------v------------+     +--------------v-----------+
+-----------v--------------+   |    |IHC_local_remote_config()|    |IHC_local_remote_config()|     |IHC_local_remote_config()|     |IHC_local_remote_config()|
|IHC_local_remote_config() |   |    | channel 1 <> 0 config    |    | channel 1 <> 0 config    |     | channel 1 <> 0 config    |     | channel 4 <> 0 config    |
| channel 0 <> 2 config    |   |    +--------------------------+    +-------------+------------+     +-------------+------------+     +--------------+-----------+
+--------------------------+   |                                                  |                                |                                 |
            |                  |    +--------------------------+                  v                                v                  +--------------v-----------+
+-----------v--------------+   |    |IHC_local_remote_config()|                                                                      |IHC_local_remote_config()|
|IHC_local_remote_config() |   |    | channel A <> B config    |                                                                      | channel B <> A config    |
| channel 0 <> 3 config    |   |    +--------------------------+                                                                      +--------------+-----------+
+--------------------------+   |                |                                                                                                    |
            |                  |                v                                                                                                    v
+-----------v--------------+   |
|IHC_local_remote_config() |   |
| channel 0 <> 4 config    |   |
+--------------------------+   |
            |                  |
+-----------v---------------+  |
| Start other harts/contexts+--+
+-----------+---------------+
            |
            v

```

  --------------------------------------
  Polled Transmit and Receive Operations
  --------------------------------------
  See the function description for message_present_poll(void) below.
  Note that one side of a channel can be polled and at the same time, the other
  side can be interrupt driven.
  This is the case on hart0 where the HSS running on hart0 polls the incoming
  messages. The outgoing messages from hart0 generate local interrupt to the far
  side ( hart 1 to 4 ) via Coreplex IHC.

  ---------------------------
  Interrupt Driven Operation
  ---------------------------
  On start-up the driver uses the function IHC_local_remote_config() to
  register an interrupt handler for each incoming channel being configured.
  Below is a bare metal example of handling an incoming message:

  ```
                  +-------------------------+
                  | registered function for |
                  | incoming channel A<>B   |
                  +-----------------+-------+
     +-------------------------+    ^
     | registered function for |    |
     | incoming channel 0<>4   |    |
     +----+--------------------+    |
          ^                         |
          | Bare metal application  |
+------------------------------------------+
          | Bare metal Driver       |
          |                         |
          |                         |
          |                         |
     +----+-------------------------+--+
     |  coreplex_ihc_hart4_int()            |
     |                                 |
     |  parses IP and calls registered |
     |  interrupt associated with the  |
     |  channel                        |
     +--------+------------------------+
              ^
              |
              |
              | Interrupt from Coreplex IHCIA
              + to hart4
  ```

 *//*=========================================================================*/
#ifndef __COREPLEX_IHC_H_
#define __COREPLEX_IHC_H_ 1

#include "coreplex_ihc_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

extern IHC_TypeDef * IHC[];

/*-------------------------------------------------------------------------*//**

  ## Interrupt mapping table

  Choose the interrupt mapping used in you system
  Please see defines in coreplex_ihc.h for the default defines.
  The default values below are over-written with those in the
  coreplex_ihc_add_mapping.h file if it this is present in the boards directory.

  |driver interrupt name |default mapped fabric interrupt in the ref. design   |
  |---------------------------------| -----------------------------------------|
  | **IHCIA_hart0_INT**             | fabric_f2h_63_plic_IRQHandler            |
  | **IHCIA_hart1_INT**             | fabric_f2h_62_plic_IRQHandler            |
  | **IHCIA_hart2_INT**             | fabric_f2h_61_plic_IRQHandler            |
  | **IHCIA_hart3_INT**             | fabric_f2h_60_plic_IRQHandler            |
  | **IHCIA_hart4_INT**             | fabric_f2h_59_plic_IRQHandler            |

 */
#ifndef IHCIA_hart0_IRQHandler
#define IHCIA_hart0_IRQHandler fabric_f2h_63_plic_IRQHandler
#endif
#ifndef IHCIA_hart1_IRQHandler
#define IHCIA_hart1_IRQHandler fabric_f2h_62_plic_IRQHandler
#endif
#ifndef IHCIA_hart2_IRQHandler
#define IHCIA_hart2_IRQHandler fabric_f2h_61_plic_IRQHandler
#endif
#ifndef IHCIA_hart3_IRQHandler
#define IHCIA_hart3_IRQHandler fabric_f2h_60_plic_IRQHandler
#endif
#ifndef IHCIA_hart4_IRQHandler
#define IHCIA_hart4_IRQHandler fabric_f2h_59_plic_IRQHandler
#endif

#ifndef IHCIA_hart0_INT
#define IHCIA_hart0_INT  PLIC_F2M_63_INT_OFFSET
#endif

#ifndef IHCIA_hart1_INT
#define IHCIA_hart1_INT  PLIC_F2M_62_INT_OFFSET
#endif

#ifndef IHCIA_hart2_INT
#define IHCIA_hart2_INT  PLIC_F2M_61_INT_OFFSET
#endif

#ifndef IHCIA_hart3_INT
#define IHCIA_hart3_INT  PLIC_F2M_60_INT_OFFSET
#endif

#ifndef IHCIA_hart4_INT
#define IHCIA_hart4_INT  PLIC_F2M_59_INT_OFFSET
#endif


/*-------------------------------------------------------------------------*//**

  ## Channel definitions

  Choose the interrupt mapping used in you system
  Please see coreplex_ihc_regs.h for the defaults
  The default values below are over-written with those in the
  coreplex_ihc_add_mapping.h file if it this is present in the platform directory.

  |value | channel                      |comment                               |
  |------|------------------------------| -------------------------------------|
  | 0    | **IHC_CHANNEL_TO_HART0**     | channel connected to hart 0          |
  | 1    | **IHC_CHANNEL_TO_HART1**     | channel connected to hart 1          |
  | 2    | **IHC_CHANNEL_TO_HART2**     | channel connected to hart 2          |
  | 3    | **IHC_CHANNEL_TO_HART3**     | channel connected to hart 3          |
  | 4    | **IHC_CHANNEL_TO_HART4**     | channel context A                    |
  | 6    | **IHC_CHANNEL_TO_CONTEXTB**  | channel context B                    |

 */
typedef enum IHC_CHANNEL_
{
    IHC_CHANNEL_TO_HART0              = 0x00,   /*!< your hart to hart 0 */
    IHC_CHANNEL_TO_HART1              = 0x01,   /*!< your hart to hart 1 */
    IHC_CHANNEL_TO_HART2              = 0x02,   /*!< your hart to hart 2 */
    IHC_CHANNEL_TO_HART3              = 0x03,   /*!< your hart to hart 3 */
    IHC_CHANNEL_TO_HART4              = 0x04,   /*!< your hart to hart 4 */
    IHC_CHANNEL_TO_CONTEXTA           = 0x05,   /*!< your hart to context A */
    IHC_CHANNEL_TO_CONTEXTB           = 0x06,   /*!< your hart to context B */
}   IHC_CHANNEL;

/*-------------------------------------------------------------------------*//**
  These hold pointers to IP associated with each hart
  Generally the mapping is fixed between Libero designs to keep thing obvious
  but it can change. The base addresses are located in the mapping header file.
 */
extern IHC_TypeDef                  IHC_H0_IP_GROUP;
extern IHC_TypeDef                  IHC_H1_IP_GROUP;
extern IHC_TypeDef                  IHC_H2_IP_GROUP;
extern IHC_TypeDef                  IHC_H3_IP_GROUP;
extern IHC_TypeDef                  IHC_H4_IP_GROUP;

/*--------------------------------Public APIs---------------------------------*/

/*-------------------------------------------------------------------------*//**
  The IHC_global_init() function initializes the IP. It is the first function
  called that accesses the Coreplex IHC.
  It must be called from the monitor hart before other harts try and access the
  Coreplex IHC. It assumes access to the full memory map. It initializes regs to
  default values which will later be updated using a local init function called
  from the Hart using the particular channels related to it hartid in the
  Coreplex IHC.

  @param
    No parameters

  @return
    This function does not return a value.

  @code
      // Initialization code
      #include "mss_ihc.h"
      int main(void)
      {

	    // The IHC_global_init() function initializes the Coreplex IHC subsystem.
	    // It is the first function called that accesses the Coreplex IHC. it must
	    // be called from the monitor hart before other harts try and access
	    // the Coreplex IHC. It assumes access to the full memory map.
	    // It sets up the base address points to reference the Coreplex IHC
	    // subsystem IHCC and IHCIA IP blocks, and sets registers to default
	    // values.

        IHC_global_init();

        uint32_t local_hartid = HSS_HART_ID;
        IHC_local_context_init((uint32_t)local_hartid);

        {
            uint32_t remote_hart_id = HART1_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART2_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART3_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART4_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }
        return (0u);
      }
  @endcode
 */
void IHC_global_init
(
    void
);

/*-------------------------------------------------------------------------*//**
  The IHC_local_context_init() function initializes the IP. It is called from
  each hart using the Coreplex IHC once on start-up.
  @param
    No parameters

  @return
    This function does not return a value.

  @code
      // Initialization code
      #include "mss_ihc.h"
      int main(void)
      {

	    // The IHC_global_init() function initializes the Coreplex IHC subsystem.
	    // It is the first function called that accesses the Coreplex IHC. it must
	    // be called from the monitor hart before other harts try and access
	    // the Coreplex IHC. It assumes access to the full memory map.
	    // It sets up the base address points to reference the Coreplex IHC
	    // subsystem IHCC and IHCIA IP blocks, and sets registers to default
	    // values.

        IHC_global_init();

        uint32_t local_hartid = HSS_HART_ID;
        IHC_local_context_init((uint32_t)local_hartid);

        {
            uint32_t remote_hart_id = HART1_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART2_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART3_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART4_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }
        return (0u);
      }
  @endcode
 */
void IHC_local_context_init(uint32_t hart_to_configure);

/*-------------------------------------------------------------------------*//**
  The IIHC_local_remote_config() function initializes the IP. It is called from
  each hart using the inter hart comms once for every hart ot context the local
  hart is communicating with.
  @param
    No parameters

  @return
    This function does not return a value.

  @code
      // Initialization code
      #include "mss_ihc.h"
      int main(void)
      {

	    // The IHC_global_init() function initializes the Coreplex IHC subsystem.
	    // It is the first function called that accesses the Coreplex IHC. it must
	    // be called from the monitor hart before other harts try and access
	    // the Coreplex IHC. It assumes access to the full memory map.
	    // It sets up the base address points to reference the Coreplex IHC
	    // subsystem IHCC and IHCIA IP blocks, and sets registers to default
	    // values.

        IHC_global_init();

        uint32_t local_hartid = HSS_HART_ID;
        IHC_local_context_init((uint32_t)local_hartid);

        {
            uint32_t remote_hart_id = HART1_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART2_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART3_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }

        {
            uint32_t remote_hart_id = HART4_ID;
            bool set_mpie_en = true;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, queue_incoming_hss_main, set_mpie_en, set_ack_en);
        }
        return (0u);
      }
  @endcode
 */
void IHC_local_remote_config(uint32_t hart_to_configure, uint32_t remote_hart_id, QUEUE_IHC_INCOMING  handler, bool set_mpie_en, bool set_ack_en );


/*-------------------------------------------------------------------------*//**
  The IHC_hart_to_context_or_hart_id() Returns the lowest hart ID of the context
  the local hart is in.

  @param channel
    The channel we want the local hart ID of.

  @return
    hartID

  @code
        // example code showing use
        uint32_t my_hart_id = context_to_local_hart_id(channel);
        uint32_t remote_hart_id = context_to_remote_hart_id(channel);
        uint32_t message_size = IHC[my_hart_id]->HART_IHC[remote_hart_id]->size_msg;
  @endcode
 */
uint32_t IHC_hart_to_context_or_hart_id(IHC_CHANNEL channel);

/*-------------------------------------------------------------------------*//**
  The IHC_context_to_context_hart_id() Returns the lowest hart ID of the context
  the hart is in.

  @param channel
    The channel we want the remote hart ID of.

  @return
    hartID

  @code
        // example code showing use
        uint32_t my_hart_id = IHC_partner_context_hart_id(remote_channel);
        uint32_t remote_hart_id = IHC_context_to_context_hart_id(remote_channel);
        uint32_t message_size = IHC[my_hart_id]->HART_IHC[remote_hart_id]->size_msg;
  @endcode
 */
extern uint32_t IHC_context_to_context_hart_id(IHC_CHANNEL remote_channel);

/*-------------------------------------------------------------------------*//**
  The IHC_partner_context_hart_id() Returns the lowest hart ID of the context
  the hart is in.

  @param remote_channel
    The channel we want the remote hart ID of.

  @return
    hartID

  @code
        // example code showing use
        uint32_t my_hart_id = IHC_partner_context_hart_id(remote_channel);
        uint32_t remote_hart_id = IHC_context_to_context_hart_id(remote_channel);
        uint32_t message_size = IHC[my_hart_id]->HART_IHC[remote_hart_id]->size_msg;
  @endcode
 */
extern uint32_t IHC_partner_context_hart_id(IHC_CHANNEL channel);

/*-------------------------------------------------------------------------*//**
  The IHC_tx_message_from_context()
  Is used to send a message to a context from a context.

  @param channel
    The channel we want the remote hart ID of.

  @param message
    Pointer to message being sent

  @return status
    hartID

  @code
        // example code showing use
        if ( MESSAGE_SENT == IHC_tx_message_from_context(IHC_CHANNEL_TO_HART0, (uint32_t *)&tx_message_buffer[0]))
        {
            // message has been sent
        }
        else
        {
            // you can try again...
  @endcode
 */
extern uint32_t IHC_tx_message_from_context(IHC_CHANNEL channel, uint32_t *message);

/*-------------------------------------------------------------------------*//**
  The IHC_tx_message_from_hart()
  Is used to send a message from non-context based upper layer (i.e. HSS) when
  you want to send a message directly to a HART or a context.

  @param channel
    The channel we want the remote hart ID of.

  @param message
    Pointer to message being sent

  @return status
    hartID

  @code
        // example code showing use
        if ( MESSAGE_SENT == IHC_tx_message_from_hart(IHC_CHANNEL_TO_HART0, (uint32_t *)&tx_message_buffer[0]))
        {
            // message has been sent
        }
        else
        {
            // you can try again...
  @endcode
 */
extern uint32_t IHC_tx_message_from_hart(IHC_CHANNEL channel, uint32_t *message);

/*-------------------------------------------------------------------------*//**
  The IHC_message_present_poll()
  When calls parse to see if message present and processes the message with
  message present handler previous registered using the
  IHC_local_remote_config() function

  @param none

  @return none

  @code
        // example code showing use
        uint32_t local_hartid = HSS_HART_ID;
        IHC_local_context_init((uint32_t)local_hartid);
        {
            uint32_t remote_hart_id = HART1_ID;
            bool set_mpie_en = false;
            bool set_ack_en = false;
            IHC_local_remote_config((uint32_t)local_hartid, remote_hart_id, our_message_handler, set_mpie_en, set_ack_en);
        }
        while(1)
        {
            // poll for incoming messages
            // if message present it is handled using our_message_handler()
            // register earlier, and written by you based on one of the examples
            // in the example programs bundled with this driver
            IHC_message_present_poll();
            // ..
  @endcode
 */
void  IHC_message_present_poll(void);

/*-------------------------------------------------------------------------*//**
  The IHC_context_indirect_isr()
  When called parse to see if message present and processes the message with
  message present handler previous registered using the
  IHC_local_remote_config() function. When we call this function we already
  have worked out our hart ID and have our message storage pointer.
  One use case is when openSBI handler when called by an upper layer.
  Below is a simplified flow diagram:

  ```
       +--------------------------+
       |Remote Processor Messaging|
       |(RPMsg) linux driver      |
       |         s-mode           |
       +------+------------+----+-+
              ^            |    ^
              |            |    |
    delegate to s-mode     |    | ecall to m-mode handler
              |            |    | returns with message pointer
              |            v    |
+-------------+----+    +--+----+--------------+
|Coreplex IHCIA    |    |                      |
|fabric interrupt  |    |HSS_SBI_ECALL_Handler |
|openSBI_int_handler    |m-mode                |
|m-mode            |    |                      |
+---------+--------+    +--+----+--------------+
          ^                |    ^
          |        +-------v----+------------------+
    MP interrupt   | IHC_context_indirect_isr()    |
          |        +-------------------------------+
          +

  ```

  @param message_storage_ptr
      where we want to store the incoming message

  @return none

  @code
        // see example application
  @endcode
 */
void  IHC_context_indirect_isr(uint32_t * message_storage_ptr);


#ifdef __cplusplus
}
#endif

#endif /* __COREPLEX_IHC_H_ */
