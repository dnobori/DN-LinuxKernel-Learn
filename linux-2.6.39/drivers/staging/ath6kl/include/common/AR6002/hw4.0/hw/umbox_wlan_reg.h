#include "linux/generated/autoconf.h"
// ------------------------------------------------------------------
// Copyright (c) 2004-2010 Atheros Corporation.  All rights reserved.
// 
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
//
// ------------------------------------------------------------------
//===================================================================
// Author(s): ="Atheros"
//===================================================================


#ifndef _UMBOX_WLAN_REG_REG_H_
#define _UMBOX_WLAN_REG_REG_H_

#define UMBOX_FIFO_ADDRESS                       0x00000000
#define UMBOX_FIFO_OFFSET                        0x00000000
#define UMBOX_FIFO_DATA_MSB                      8
#define UMBOX_FIFO_DATA_LSB                      0
#define UMBOX_FIFO_DATA_MASK                     0x000001ff
#define UMBOX_FIFO_DATA_GET(x)                   (((x) & UMBOX_FIFO_DATA_MASK) >> UMBOX_FIFO_DATA_LSB)
#define UMBOX_FIFO_DATA_SET(x)                   (((x) << UMBOX_FIFO_DATA_LSB) & UMBOX_FIFO_DATA_MASK)

#define UMBOX_FIFO_STATUS_ADDRESS                0x00000008
#define UMBOX_FIFO_STATUS_OFFSET                 0x00000008
#define UMBOX_FIFO_STATUS_TX_EMPTY_MSB           3
#define UMBOX_FIFO_STATUS_TX_EMPTY_LSB           3
#define UMBOX_FIFO_STATUS_TX_EMPTY_MASK          0x00000008
#define UMBOX_FIFO_STATUS_TX_EMPTY_GET(x)        (((x) & UMBOX_FIFO_STATUS_TX_EMPTY_MASK) >> UMBOX_FIFO_STATUS_TX_EMPTY_LSB)
#define UMBOX_FIFO_STATUS_TX_EMPTY_SET(x)        (((x) << UMBOX_FIFO_STATUS_TX_EMPTY_LSB) & UMBOX_FIFO_STATUS_TX_EMPTY_MASK)
#define UMBOX_FIFO_STATUS_TX_FULL_MSB            2
#define UMBOX_FIFO_STATUS_TX_FULL_LSB            2
#define UMBOX_FIFO_STATUS_TX_FULL_MASK           0x00000004
#define UMBOX_FIFO_STATUS_TX_FULL_GET(x)         (((x) & UMBOX_FIFO_STATUS_TX_FULL_MASK) >> UMBOX_FIFO_STATUS_TX_FULL_LSB)
#define UMBOX_FIFO_STATUS_TX_FULL_SET(x)         (((x) << UMBOX_FIFO_STATUS_TX_FULL_LSB) & UMBOX_FIFO_STATUS_TX_FULL_MASK)
#define UMBOX_FIFO_STATUS_RX_EMPTY_MSB           1
#define UMBOX_FIFO_STATUS_RX_EMPTY_LSB           1
#define UMBOX_FIFO_STATUS_RX_EMPTY_MASK          0x00000002
#define UMBOX_FIFO_STATUS_RX_EMPTY_GET(x)        (((x) & UMBOX_FIFO_STATUS_RX_EMPTY_MASK) >> UMBOX_FIFO_STATUS_RX_EMPTY_LSB)
#define UMBOX_FIFO_STATUS_RX_EMPTY_SET(x)        (((x) << UMBOX_FIFO_STATUS_RX_EMPTY_LSB) & UMBOX_FIFO_STATUS_RX_EMPTY_MASK)
#define UMBOX_FIFO_STATUS_RX_FULL_MSB            0
#define UMBOX_FIFO_STATUS_RX_FULL_LSB            0
#define UMBOX_FIFO_STATUS_RX_FULL_MASK           0x00000001
#define UMBOX_FIFO_STATUS_RX_FULL_GET(x)         (((x) & UMBOX_FIFO_STATUS_RX_FULL_MASK) >> UMBOX_FIFO_STATUS_RX_FULL_LSB)
#define UMBOX_FIFO_STATUS_RX_FULL_SET(x)         (((x) << UMBOX_FIFO_STATUS_RX_FULL_LSB) & UMBOX_FIFO_STATUS_RX_FULL_MASK)

#define UMBOX_DMA_POLICY_ADDRESS                 0x0000000c
#define UMBOX_DMA_POLICY_OFFSET                  0x0000000c
#define UMBOX_DMA_POLICY_TX_QUANTUM_MSB          3
#define UMBOX_DMA_POLICY_TX_QUANTUM_LSB          3
#define UMBOX_DMA_POLICY_TX_QUANTUM_MASK         0x00000008
#define UMBOX_DMA_POLICY_TX_QUANTUM_GET(x)       (((x) & UMBOX_DMA_POLICY_TX_QUANTUM_MASK) >> UMBOX_DMA_POLICY_TX_QUANTUM_LSB)
#define UMBOX_DMA_POLICY_TX_QUANTUM_SET(x)       (((x) << UMBOX_DMA_POLICY_TX_QUANTUM_LSB) & UMBOX_DMA_POLICY_TX_QUANTUM_MASK)
#define UMBOX_DMA_POLICY_TX_ORDER_MSB            2
#define UMBOX_DMA_POLICY_TX_ORDER_LSB            2
#define UMBOX_DMA_POLICY_TX_ORDER_MASK           0x00000004
#define UMBOX_DMA_POLICY_TX_ORDER_GET(x)         (((x) & UMBOX_DMA_POLICY_TX_ORDER_MASK) >> UMBOX_DMA_POLICY_TX_ORDER_LSB)
#define UMBOX_DMA_POLICY_TX_ORDER_SET(x)         (((x) << UMBOX_DMA_POLICY_TX_ORDER_LSB) & UMBOX_DMA_POLICY_TX_ORDER_MASK)
#define UMBOX_DMA_POLICY_RX_QUANTUM_MSB          1
#define UMBOX_DMA_POLICY_RX_QUANTUM_LSB          1
#define UMBOX_DMA_POLICY_RX_QUANTUM_MASK         0x00000002
#define UMBOX_DMA_POLICY_RX_QUANTUM_GET(x)       (((x) & UMBOX_DMA_POLICY_RX_QUANTUM_MASK) >> UMBOX_DMA_POLICY_RX_QUANTUM_LSB)
#define UMBOX_DMA_POLICY_RX_QUANTUM_SET(x)       (((x) << UMBOX_DMA_POLICY_RX_QUANTUM_LSB) & UMBOX_DMA_POLICY_RX_QUANTUM_MASK)
#define UMBOX_DMA_POLICY_RX_ORDER_MSB            0
#define UMBOX_DMA_POLICY_RX_ORDER_LSB            0
#define UMBOX_DMA_POLICY_RX_ORDER_MASK           0x00000001
#define UMBOX_DMA_POLICY_RX_ORDER_GET(x)         (((x) & UMBOX_DMA_POLICY_RX_ORDER_MASK) >> UMBOX_DMA_POLICY_RX_ORDER_LSB)
#define UMBOX_DMA_POLICY_RX_ORDER_SET(x)         (((x) << UMBOX_DMA_POLICY_RX_ORDER_LSB) & UMBOX_DMA_POLICY_RX_ORDER_MASK)

#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS    0x00000010
#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_OFFSET     0x00000010
#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_MSB 27
#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_LSB 2
#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_MASK 0x0ffffffc
#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_GET(x) (((x) & UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_MASK) >> UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_LSB)
#define UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_SET(x) (((x) << UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_LSB) & UMBOX0_DMA_RX_DESCRIPTOR_BASE_ADDRESS_MASK)

#define UMBOX0_DMA_RX_CONTROL_ADDRESS            0x00000014
#define UMBOX0_DMA_RX_CONTROL_OFFSET             0x00000014
#define UMBOX0_DMA_RX_CONTROL_RESUME_MSB         2
#define UMBOX0_DMA_RX_CONTROL_RESUME_LSB         2
#define UMBOX0_DMA_RX_CONTROL_RESUME_MASK        0x00000004
#define UMBOX0_DMA_RX_CONTROL_RESUME_GET(x)      (((x) & UMBOX0_DMA_RX_CONTROL_RESUME_MASK) >> UMBOX0_DMA_RX_CONTROL_RESUME_LSB)
#define UMBOX0_DMA_RX_CONTROL_RESUME_SET(x)      (((x) << UMBOX0_DMA_RX_CONTROL_RESUME_LSB) & UMBOX0_DMA_RX_CONTROL_RESUME_MASK)
#define UMBOX0_DMA_RX_CONTROL_START_MSB          1
#define UMBOX0_DMA_RX_CONTROL_START_LSB          1
#define UMBOX0_DMA_RX_CONTROL_START_MASK         0x00000002
#define UMBOX0_DMA_RX_CONTROL_START_GET(x)       (((x) & UMBOX0_DMA_RX_CONTROL_START_MASK) >> UMBOX0_DMA_RX_CONTROL_START_LSB)
#define UMBOX0_DMA_RX_CONTROL_START_SET(x)       (((x) << UMBOX0_DMA_RX_CONTROL_START_LSB) & UMBOX0_DMA_RX_CONTROL_START_MASK)
#define UMBOX0_DMA_RX_CONTROL_STOP_MSB           0
#define UMBOX0_DMA_RX_CONTROL_STOP_LSB           0
#define UMBOX0_DMA_RX_CONTROL_STOP_MASK          0x00000001
#define UMBOX0_DMA_RX_CONTROL_STOP_GET(x)        (((x) & UMBOX0_DMA_RX_CONTROL_STOP_MASK) >> UMBOX0_DMA_RX_CONTROL_STOP_LSB)
#define UMBOX0_DMA_RX_CONTROL_STOP_SET(x)        (((x) << UMBOX0_DMA_RX_CONTROL_STOP_LSB) & UMBOX0_DMA_RX_CONTROL_STOP_MASK)

#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS    0x00000018
#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_OFFSET     0x00000018
#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_MSB 27
#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_LSB 2
#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_MASK 0x0ffffffc
#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_GET(x) (((x) & UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_MASK) >> UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_LSB)
#define UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_SET(x) (((x) << UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_LSB) & UMBOX0_DMA_TX_DESCRIPTOR_BASE_ADDRESS_MASK)

#define UMBOX0_DMA_TX_CONTROL_ADDRESS            0x0000001c
#define UMBOX0_DMA_TX_CONTROL_OFFSET             0x0000001c
#define UMBOX0_DMA_TX_CONTROL_RESUME_MSB         2
#define UMBOX0_DMA_TX_CONTROL_RESUME_LSB         2
#define UMBOX0_DMA_TX_CONTROL_RESUME_MASK        0x00000004
#define UMBOX0_DMA_TX_CONTROL_RESUME_GET(x)      (((x) & UMBOX0_DMA_TX_CONTROL_RESUME_MASK) >> UMBOX0_DMA_TX_CONTROL_RESUME_LSB)
#define UMBOX0_DMA_TX_CONTROL_RESUME_SET(x)      (((x) << UMBOX0_DMA_TX_CONTROL_RESUME_LSB) & UMBOX0_DMA_TX_CONTROL_RESUME_MASK)
#define UMBOX0_DMA_TX_CONTROL_START_MSB          1
#define UMBOX0_DMA_TX_CONTROL_START_LSB          1
#define UMBOX0_DMA_TX_CONTROL_START_MASK         0x00000002
#define UMBOX0_DMA_TX_CONTROL_START_GET(x)       (((x) & UMBOX0_DMA_TX_CONTROL_START_MASK) >> UMBOX0_DMA_TX_CONTROL_START_LSB)
#define UMBOX0_DMA_TX_CONTROL_START_SET(x)       (((x) << UMBOX0_DMA_TX_CONTROL_START_LSB) & UMBOX0_DMA_TX_CONTROL_START_MASK)
#define UMBOX0_DMA_TX_CONTROL_STOP_MSB           0
#define UMBOX0_DMA_TX_CONTROL_STOP_LSB           0
#define UMBOX0_DMA_TX_CONTROL_STOP_MASK          0x00000001
#define UMBOX0_DMA_TX_CONTROL_STOP_GET(x)        (((x) & UMBOX0_DMA_TX_CONTROL_STOP_MASK) >> UMBOX0_DMA_TX_CONTROL_STOP_LSB)
#define UMBOX0_DMA_TX_CONTROL_STOP_SET(x)        (((x) << UMBOX0_DMA_TX_CONTROL_STOP_LSB) & UMBOX0_DMA_TX_CONTROL_STOP_MASK)

#define UMBOX_FIFO_TIMEOUT_ADDRESS               0x00000020
#define UMBOX_FIFO_TIMEOUT_OFFSET                0x00000020
#define UMBOX_FIFO_TIMEOUT_ENABLE_SET_MSB        8
#define UMBOX_FIFO_TIMEOUT_ENABLE_SET_LSB        8
#define UMBOX_FIFO_TIMEOUT_ENABLE_SET_MASK       0x00000100
#define UMBOX_FIFO_TIMEOUT_ENABLE_SET_GET(x)     (((x) & UMBOX_FIFO_TIMEOUT_ENABLE_SET_MASK) >> UMBOX_FIFO_TIMEOUT_ENABLE_SET_LSB)
#define UMBOX_FIFO_TIMEOUT_ENABLE_SET_SET(x)     (((x) << UMBOX_FIFO_TIMEOUT_ENABLE_SET_LSB) & UMBOX_FIFO_TIMEOUT_ENABLE_SET_MASK)
#define UMBOX_FIFO_TIMEOUT_VALUE_MSB             7
#define UMBOX_FIFO_TIMEOUT_VALUE_LSB             0
#define UMBOX_FIFO_TIMEOUT_VALUE_MASK            0x000000ff
#define UMBOX_FIFO_TIMEOUT_VALUE_GET(x)          (((x) & UMBOX_FIFO_TIMEOUT_VALUE_MASK) >> UMBOX_FIFO_TIMEOUT_VALUE_LSB)
#define UMBOX_FIFO_TIMEOUT_VALUE_SET(x)          (((x) << UMBOX_FIFO_TIMEOUT_VALUE_LSB) & UMBOX_FIFO_TIMEOUT_VALUE_MASK)

#define UMBOX_INT_STATUS_ADDRESS                 0x00000024
#define UMBOX_INT_STATUS_OFFSET                  0x00000024
#define UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_MSB 9
#define UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_LSB 9
#define UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_MASK 0x00000200
#define UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_GET(x) (((x) & UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_MASK) >> UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_LSB)
#define UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_SET(x) (((x) << UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_LSB) & UMBOX_INT_STATUS_HCI_FRAMER_UNDERFLOW_MASK)
#define UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_MSB 8
#define UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_LSB 8
#define UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_MASK 0x00000100
#define UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_GET(x) (((x) & UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_MASK) >> UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_LSB)
#define UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_SET(x) (((x) << UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_LSB) & UMBOX_INT_STATUS_HCI_FRAMER_OVERFLOW_MASK)
#define UMBOX_INT_STATUS_RX_DMA_COMPLETE_MSB     7
#define UMBOX_INT_STATUS_RX_DMA_COMPLETE_LSB     7
#define UMBOX_INT_STATUS_RX_DMA_COMPLETE_MASK    0x00000080
#define UMBOX_INT_STATUS_RX_DMA_COMPLETE_GET(x)  (((x) & UMBOX_INT_STATUS_RX_DMA_COMPLETE_MASK) >> UMBOX_INT_STATUS_RX_DMA_COMPLETE_LSB)
#define UMBOX_INT_STATUS_RX_DMA_COMPLETE_SET(x)  (((x) << UMBOX_INT_STATUS_RX_DMA_COMPLETE_LSB) & UMBOX_INT_STATUS_RX_DMA_COMPLETE_MASK)
#define UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_MSB 6
#define UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_LSB 6
#define UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_MASK 0x00000040
#define UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_GET(x) (((x) & UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_MASK) >> UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_LSB)
#define UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_SET(x) (((x) << UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_LSB) & UMBOX_INT_STATUS_TX_DMA_EOM_COMPLETE_MASK)
#define UMBOX_INT_STATUS_TX_DMA_COMPLETE_MSB     5
#define UMBOX_INT_STATUS_TX_DMA_COMPLETE_LSB     5
#define UMBOX_INT_STATUS_TX_DMA_COMPLETE_MASK    0x00000020
#define UMBOX_INT_STATUS_TX_DMA_COMPLETE_GET(x)  (((x) & UMBOX_INT_STATUS_TX_DMA_COMPLETE_MASK) >> UMBOX_INT_STATUS_TX_DMA_COMPLETE_LSB)
#define UMBOX_INT_STATUS_TX_DMA_COMPLETE_SET(x)  (((x) << UMBOX_INT_STATUS_TX_DMA_COMPLETE_LSB) & UMBOX_INT_STATUS_TX_DMA_COMPLETE_MASK)
#define UMBOX_INT_STATUS_HCI_SYNC_ERROR_MSB      4
#define UMBOX_INT_STATUS_HCI_SYNC_ERROR_LSB      4
#define UMBOX_INT_STATUS_HCI_SYNC_ERROR_MASK     0x00000010
#define UMBOX_INT_STATUS_HCI_SYNC_ERROR_GET(x)   (((x) & UMBOX_INT_STATUS_HCI_SYNC_ERROR_MASK) >> UMBOX_INT_STATUS_HCI_SYNC_ERROR_LSB)
#define UMBOX_INT_STATUS_HCI_SYNC_ERROR_SET(x)   (((x) << UMBOX_INT_STATUS_HCI_SYNC_ERROR_LSB) & UMBOX_INT_STATUS_HCI_SYNC_ERROR_MASK)
#define UMBOX_INT_STATUS_TX_OVERFLOW_MSB         3
#define UMBOX_INT_STATUS_TX_OVERFLOW_LSB         3
#define UMBOX_INT_STATUS_TX_OVERFLOW_MASK        0x00000008
#define UMBOX_INT_STATUS_TX_OVERFLOW_GET(x)      (((x) & UMBOX_INT_STATUS_TX_OVERFLOW_MASK) >> UMBOX_INT_STATUS_TX_OVERFLOW_LSB)
#define UMBOX_INT_STATUS_TX_OVERFLOW_SET(x)      (((x) << UMBOX_INT_STATUS_TX_OVERFLOW_LSB) & UMBOX_INT_STATUS_TX_OVERFLOW_MASK)
#define UMBOX_INT_STATUS_RX_UNDERFLOW_MSB        2
#define UMBOX_INT_STATUS_RX_UNDERFLOW_LSB        2
#define UMBOX_INT_STATUS_RX_UNDERFLOW_MASK       0x00000004
#define UMBOX_INT_STATUS_RX_UNDERFLOW_GET(x)     (((x) & UMBOX_INT_STATUS_RX_UNDERFLOW_MASK) >> UMBOX_INT_STATUS_RX_UNDERFLOW_LSB)
#define UMBOX_INT_STATUS_RX_UNDERFLOW_SET(x)     (((x) << UMBOX_INT_STATUS_RX_UNDERFLOW_LSB) & UMBOX_INT_STATUS_RX_UNDERFLOW_MASK)
#define UMBOX_INT_STATUS_TX_NOT_EMPTY_MSB        1
#define UMBOX_INT_STATUS_TX_NOT_EMPTY_LSB        1
#define UMBOX_INT_STATUS_TX_NOT_EMPTY_MASK       0x00000002
#define UMBOX_INT_STATUS_TX_NOT_EMPTY_GET(x)     (((x) & UMBOX_INT_STATUS_TX_NOT_EMPTY_MASK) >> UMBOX_INT_STATUS_TX_NOT_EMPTY_LSB)
#define UMBOX_INT_STATUS_TX_NOT_EMPTY_SET(x)     (((x) << UMBOX_INT_STATUS_TX_NOT_EMPTY_LSB) & UMBOX_INT_STATUS_TX_NOT_EMPTY_MASK)
#define UMBOX_INT_STATUS_RX_NOT_FULL_MSB         0
#define UMBOX_INT_STATUS_RX_NOT_FULL_LSB         0
#define UMBOX_INT_STATUS_RX_NOT_FULL_MASK        0x00000001
#define UMBOX_INT_STATUS_RX_NOT_FULL_GET(x)      (((x) & UMBOX_INT_STATUS_RX_NOT_FULL_MASK) >> UMBOX_INT_STATUS_RX_NOT_FULL_LSB)
#define UMBOX_INT_STATUS_RX_NOT_FULL_SET(x)      (((x) << UMBOX_INT_STATUS_RX_NOT_FULL_LSB) & UMBOX_INT_STATUS_RX_NOT_FULL_MASK)

#define UMBOX_INT_ENABLE_ADDRESS                 0x00000028
#define UMBOX_INT_ENABLE_OFFSET                  0x00000028
#define UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_MSB 9
#define UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_LSB 9
#define UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_MASK 0x00000200
#define UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_GET(x) (((x) & UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_MASK) >> UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_LSB)
#define UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_SET(x) (((x) << UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_LSB) & UMBOX_INT_ENABLE_HCI_FRAMER_UNDERFLOW_MASK)
#define UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_MSB 8
#define UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_LSB 8
#define UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_MASK 0x00000100
#define UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_GET(x) (((x) & UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_MASK) >> UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_LSB)
#define UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_SET(x) (((x) << UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_LSB) & UMBOX_INT_ENABLE_HCI_FRAMER_OVERFLOW_MASK)
#define UMBOX_INT_ENABLE_RX_DMA_COMPLETE_MSB     7
#define UMBOX_INT_ENABLE_RX_DMA_COMPLETE_LSB     7
#define UMBOX_INT_ENABLE_RX_DMA_COMPLETE_MASK    0x00000080
#define UMBOX_INT_ENABLE_RX_DMA_COMPLETE_GET(x)  (((x) & UMBOX_INT_ENABLE_RX_DMA_COMPLETE_MASK) >> UMBOX_INT_ENABLE_RX_DMA_COMPLETE_LSB)
#define UMBOX_INT_ENABLE_RX_DMA_COMPLETE_SET(x)  (((x) << UMBOX_INT_ENABLE_RX_DMA_COMPLETE_LSB) & UMBOX_INT_ENABLE_RX_DMA_COMPLETE_MASK)
#define UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_MSB 6
#define UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_LSB 6
#define UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_MASK 0x00000040
#define UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_GET(x) (((x) & UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_MASK) >> UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_LSB)
#define UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_SET(x) (((x) << UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_LSB) & UMBOX_INT_ENABLE_TX_DMA_EOM_COMPLETE_MASK)
#define UMBOX_INT_ENABLE_TX_DMA_COMPLETE_MSB     5
#define UMBOX_INT_ENABLE_TX_DMA_COMPLETE_LSB     5
#define UMBOX_INT_ENABLE_TX_DMA_COMPLETE_MASK    0x00000020
#define UMBOX_INT_ENABLE_TX_DMA_COMPLETE_GET(x)  (((x) & UMBOX_INT_ENABLE_TX_DMA_COMPLETE_MASK) >> UMBOX_INT_ENABLE_TX_DMA_COMPLETE_LSB)
#define UMBOX_INT_ENABLE_TX_DMA_COMPLETE_SET(x)  (((x) << UMBOX_INT_ENABLE_TX_DMA_COMPLETE_LSB) & UMBOX_INT_ENABLE_TX_DMA_COMPLETE_MASK)
#define UMBOX_INT_ENABLE_HCI_SYNC_ERROR_MSB      4
#define UMBOX_INT_ENABLE_HCI_SYNC_ERROR_LSB      4
#define UMBOX_INT_ENABLE_HCI_SYNC_ERROR_MASK     0x00000010
#define UMBOX_INT_ENABLE_HCI_SYNC_ERROR_GET(x)   (((x) & UMBOX_INT_ENABLE_HCI_SYNC_ERROR_MASK) >> UMBOX_INT_ENABLE_HCI_SYNC_ERROR_LSB)
#define UMBOX_INT_ENABLE_HCI_SYNC_ERROR_SET(x)   (((x) << UMBOX_INT_ENABLE_HCI_SYNC_ERROR_LSB) & UMBOX_INT_ENABLE_HCI_SYNC_ERROR_MASK)
#define UMBOX_INT_ENABLE_TX_OVERFLOW_MSB         3
#define UMBOX_INT_ENABLE_TX_OVERFLOW_LSB         3
#define UMBOX_INT_ENABLE_TX_OVERFLOW_MASK        0x00000008
#define UMBOX_INT_ENABLE_TX_OVERFLOW_GET(x)      (((x) & UMBOX_INT_ENABLE_TX_OVERFLOW_MASK) >> UMBOX_INT_ENABLE_TX_OVERFLOW_LSB)
#define UMBOX_INT_ENABLE_TX_OVERFLOW_SET(x)      (((x) << UMBOX_INT_ENABLE_TX_OVERFLOW_LSB) & UMBOX_INT_ENABLE_TX_OVERFLOW_MASK)
#define UMBOX_INT_ENABLE_RX_UNDERFLOW_MSB        2
#define UMBOX_INT_ENABLE_RX_UNDERFLOW_LSB        2
#define UMBOX_INT_ENABLE_RX_UNDERFLOW_MASK       0x00000004
#define UMBOX_INT_ENABLE_RX_UNDERFLOW_GET(x)     (((x) & UMBOX_INT_ENABLE_RX_UNDERFLOW_MASK) >> UMBOX_INT_ENABLE_RX_UNDERFLOW_LSB)
#define UMBOX_INT_ENABLE_RX_UNDERFLOW_SET(x)     (((x) << UMBOX_INT_ENABLE_RX_UNDERFLOW_LSB) & UMBOX_INT_ENABLE_RX_UNDERFLOW_MASK)
#define UMBOX_INT_ENABLE_TX_NOT_EMPTY_MSB        1
#define UMBOX_INT_ENABLE_TX_NOT_EMPTY_LSB        1
#define UMBOX_INT_ENABLE_TX_NOT_EMPTY_MASK       0x00000002
#define UMBOX_INT_ENABLE_TX_NOT_EMPTY_GET(x)     (((x) & UMBOX_INT_ENABLE_TX_NOT_EMPTY_MASK) >> UMBOX_INT_ENABLE_TX_NOT_EMPTY_LSB)
#define UMBOX_INT_ENABLE_TX_NOT_EMPTY_SET(x)     (((x) << UMBOX_INT_ENABLE_TX_NOT_EMPTY_LSB) & UMBOX_INT_ENABLE_TX_NOT_EMPTY_MASK)
#define UMBOX_INT_ENABLE_RX_NOT_FULL_MSB         0
#define UMBOX_INT_ENABLE_RX_NOT_FULL_LSB         0
#define UMBOX_INT_ENABLE_RX_NOT_FULL_MASK        0x00000001
#define UMBOX_INT_ENABLE_RX_NOT_FULL_GET(x)      (((x) & UMBOX_INT_ENABLE_RX_NOT_FULL_MASK) >> UMBOX_INT_ENABLE_RX_NOT_FULL_LSB)
#define UMBOX_INT_ENABLE_RX_NOT_FULL_SET(x)      (((x) << UMBOX_INT_ENABLE_RX_NOT_FULL_LSB) & UMBOX_INT_ENABLE_RX_NOT_FULL_MASK)

#define UMBOX_DEBUG_ADDRESS                      0x0000002c
#define UMBOX_DEBUG_OFFSET                       0x0000002c
#define UMBOX_DEBUG_SEL_MSB                      2
#define UMBOX_DEBUG_SEL_LSB                      0
#define UMBOX_DEBUG_SEL_MASK                     0x00000007
#define UMBOX_DEBUG_SEL_GET(x)                   (((x) & UMBOX_DEBUG_SEL_MASK) >> UMBOX_DEBUG_SEL_LSB)
#define UMBOX_DEBUG_SEL_SET(x)                   (((x) << UMBOX_DEBUG_SEL_LSB) & UMBOX_DEBUG_SEL_MASK)

#define UMBOX_FIFO_RESET_ADDRESS                 0x00000030
#define UMBOX_FIFO_RESET_OFFSET                  0x00000030
#define UMBOX_FIFO_RESET_INIT_MSB                0
#define UMBOX_FIFO_RESET_INIT_LSB                0
#define UMBOX_FIFO_RESET_INIT_MASK               0x00000001
#define UMBOX_FIFO_RESET_INIT_GET(x)             (((x) & UMBOX_FIFO_RESET_INIT_MASK) >> UMBOX_FIFO_RESET_INIT_LSB)
#define UMBOX_FIFO_RESET_INIT_SET(x)             (((x) << UMBOX_FIFO_RESET_INIT_LSB) & UMBOX_FIFO_RESET_INIT_MASK)

#define UMBOX_HCI_FRAMER_ADDRESS                 0x00000034
#define UMBOX_HCI_FRAMER_OFFSET                  0x00000034
#define UMBOX_HCI_FRAMER_CRC_OVERRIDE_MSB        6
#define UMBOX_HCI_FRAMER_CRC_OVERRIDE_LSB        6
#define UMBOX_HCI_FRAMER_CRC_OVERRIDE_MASK       0x00000040
#define UMBOX_HCI_FRAMER_CRC_OVERRIDE_GET(x)     (((x) & UMBOX_HCI_FRAMER_CRC_OVERRIDE_MASK) >> UMBOX_HCI_FRAMER_CRC_OVERRIDE_LSB)
#define UMBOX_HCI_FRAMER_CRC_OVERRIDE_SET(x)     (((x) << UMBOX_HCI_FRAMER_CRC_OVERRIDE_LSB) & UMBOX_HCI_FRAMER_CRC_OVERRIDE_MASK)
#define UMBOX_HCI_FRAMER_ENABLE_MSB              5
#define UMBOX_HCI_FRAMER_ENABLE_LSB              5
#define UMBOX_HCI_FRAMER_ENABLE_MASK             0x00000020
#define UMBOX_HCI_FRAMER_ENABLE_GET(x)           (((x) & UMBOX_HCI_FRAMER_ENABLE_MASK) >> UMBOX_HCI_FRAMER_ENABLE_LSB)
#define UMBOX_HCI_FRAMER_ENABLE_SET(x)           (((x) << UMBOX_HCI_FRAMER_ENABLE_LSB) & UMBOX_HCI_FRAMER_ENABLE_MASK)
#define UMBOX_HCI_FRAMER_SYNC_ERROR_MSB          4
#define UMBOX_HCI_FRAMER_SYNC_ERROR_LSB          4
#define UMBOX_HCI_FRAMER_SYNC_ERROR_MASK         0x00000010
#define UMBOX_HCI_FRAMER_SYNC_ERROR_GET(x)       (((x) & UMBOX_HCI_FRAMER_SYNC_ERROR_MASK) >> UMBOX_HCI_FRAMER_SYNC_ERROR_LSB)
#define UMBOX_HCI_FRAMER_SYNC_ERROR_SET(x)       (((x) << UMBOX_HCI_FRAMER_SYNC_ERROR_LSB) & UMBOX_HCI_FRAMER_SYNC_ERROR_MASK)
#define UMBOX_HCI_FRAMER_UNDERFLOW_MSB           3
#define UMBOX_HCI_FRAMER_UNDERFLOW_LSB           3
#define UMBOX_HCI_FRAMER_UNDERFLOW_MASK          0x00000008
#define UMBOX_HCI_FRAMER_UNDERFLOW_GET(x)        (((x) & UMBOX_HCI_FRAMER_UNDERFLOW_MASK) >> UMBOX_HCI_FRAMER_UNDERFLOW_LSB)
#define UMBOX_HCI_FRAMER_UNDERFLOW_SET(x)        (((x) << UMBOX_HCI_FRAMER_UNDERFLOW_LSB) & UMBOX_HCI_FRAMER_UNDERFLOW_MASK)
#define UMBOX_HCI_FRAMER_OVERFLOW_MSB            2
#define UMBOX_HCI_FRAMER_OVERFLOW_LSB            2
#define UMBOX_HCI_FRAMER_OVERFLOW_MASK           0x00000004
#define UMBOX_HCI_FRAMER_OVERFLOW_GET(x)         (((x) & UMBOX_HCI_FRAMER_OVERFLOW_MASK) >> UMBOX_HCI_FRAMER_OVERFLOW_LSB)
#define UMBOX_HCI_FRAMER_OVERFLOW_SET(x)         (((x) << UMBOX_HCI_FRAMER_OVERFLOW_LSB) & UMBOX_HCI_FRAMER_OVERFLOW_MASK)
#define UMBOX_HCI_FRAMER_CONFIG_MODE_MSB         1
#define UMBOX_HCI_FRAMER_CONFIG_MODE_LSB         0
#define UMBOX_HCI_FRAMER_CONFIG_MODE_MASK        0x00000003
#define UMBOX_HCI_FRAMER_CONFIG_MODE_GET(x)      (((x) & UMBOX_HCI_FRAMER_CONFIG_MODE_MASK) >> UMBOX_HCI_FRAMER_CONFIG_MODE_LSB)
#define UMBOX_HCI_FRAMER_CONFIG_MODE_SET(x)      (((x) << UMBOX_HCI_FRAMER_CONFIG_MODE_LSB) & UMBOX_HCI_FRAMER_CONFIG_MODE_MASK)


#ifndef __ASSEMBLER__

typedef struct umbox_wlan_reg_reg_s {
  volatile unsigned int umbox_fifo[2];
  volatile unsigned int umbox_fifo_status;
  volatile unsigned int umbox_dma_policy;
  volatile unsigned int umbox0_dma_rx_descriptor_base;
  volatile unsigned int umbox0_dma_rx_control;
  volatile unsigned int umbox0_dma_tx_descriptor_base;
  volatile unsigned int umbox0_dma_tx_control;
  volatile unsigned int umbox_fifo_timeout;
  volatile unsigned int umbox_int_status;
  volatile unsigned int umbox_int_enable;
  volatile unsigned int umbox_debug;
  volatile unsigned int umbox_fifo_reset;
  volatile unsigned int umbox_hci_framer;
} umbox_wlan_reg_reg_t;

#endif /* __ASSEMBLER__ */

#endif /* _UMBOX_WLAN_REG_H_ */
