/**
 * @project
 * @file RingBufferWrapper.c
 * @author Daniel Dunham (Daniel.Dunham1@assaabloy.com)
 * @brief Ring Buffer             Ring buffers for various data. Add to this as needed.
 * @version X.X.X
 * @date 2025-01-28
 * @copyright Copyright (c) 2025 Norton Rixson
 */

#include <stdlib.h>

#include "RingBuffer.h"
#include "RingBufferWrapper.h"

typedef struct RingBufferWrapperInfo_t
{
    RingBuffers_e nameOfBuff;
    RingBuffWrapperError_e error;
}RingBufferWrapperInfo_t;

volatile RingBuff_Handle_t uart_TX_DBG_RB;
volatile RingBuff_Handle_t uart_RX_DBG_RB;

RingBuffWrapperError_e RingBuffInitWrapped(RingBuffers_e nameOfBuff, uint8_t* buff, size_t size)
{
    RingBufferWrapperInfo_t ringBufferInfo;
    ringBufferInfo.nameOfBuff = nameOfBuff;

    switch (ringBufferInfo.nameOfBuff) {
        case UARTRX_DBG:
            uart_RX_DBG_RB = RingBuffInit(buff, size);
            ringBufferInfo.error = RBW_NONE;
            break;
        case UARTTX_DBG:
            uart_TX_DBG_RB = RingBuffInit(buff, size);
            ringBufferInfo.error = RBW_NONE;
            break;
        default:
            ringBufferInfo.error = RBW_INVALID_BUFFER_NAME;
            break;
    }
    return ringBufferInfo.error;
}

RingBuffWrapperError_e RingBuffPutWrapped(RingBuffers_e nameOfBuff, uint8_t data)
{
    RingBufferWrapperInfo_t ringBufferInfo;
    ringBufferInfo.nameOfBuff = nameOfBuff;
    RingBuffErrors_e errorCheck = RB_UNKNOWN;

    switch (ringBufferInfo.nameOfBuff) {
        case UARTRX_DBG:
            errorCheck = RingBuffPut(uart_RX_DBG_RB, data);
            ringBufferInfo.error = RBW_NONE;
            break;
        case UARTTX_DBG:
            errorCheck = RingBuffPut(uart_TX_DBG_RB, data);
            ringBufferInfo.error = RBW_NONE;
            break;
        default:
            ringBufferInfo.error = RBW_INVALID_BUFFER_NAME;
            break;
    }

    return ringBufferInfo.error;
}

RingBuffWrapperError_e RingBuffGetWrapped(RingBuffers_e nameOfBuff, uint8_t* data)
{
    RingBufferWrapperInfo_t ringBufferInfo;
    ringBufferInfo.nameOfBuff = nameOfBuff;
    RingBuffErrors_e errorCheck = RB_UNKNOWN;

    switch (ringBufferInfo.nameOfBuff) {
        case UARTRX_DBG:
            errorCheck = RingBuffGet(uart_RX_DBG_RB, data);
            ringBufferInfo.error = RBW_NONE;
            break;
        case UARTTX_DBG:
            errorCheck = RingBuffGet(uart_TX_DBG_RB, data);
            ringBufferInfo.error = RBW_NONE;
            break;
        default:
            ringBufferInfo.error = RBW_INVALID_BUFFER_NAME;
            break;
    }

    return ringBufferInfo.error;
}

bool RingBuffEmptyWrapped(RingBuffers_e nameOfBuff)
{
    bool output = false;

    switch (nameOfBuff) {
        case UARTRX_DBG:
            output = RingBuffEmpty(uart_RX_DBG_RB);
            break;
        case UARTTX_DBG:
            output = RingBuffEmpty(uart_TX_DBG_RB);
            break;
        default:
            break;
    }
    
    return output;
}