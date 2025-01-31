/**
 * @project
 * @file RingBufferWrapper.h
 * @author Daniel Dunham (Daniel.Dunham1@assaabloy.com)
 * @brief Ring Buffer             Ring buffers for various data. Add to this as needed.
 * @version X.X.X
 * @date 2025-01-28
 * @copyright Copyright (c) 2025 Norton Rixson
 */
#ifndef RINGBUFFERWRAPPER_H_
#define RINGBUFFERWRAPPER_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum RingBuffers_e
{
    UARTRX_DBG
    UARTTX_DBG
}RingBuffers_e;

typedef enum RingBuffWrapperError_e 
{
    RBW_NONE,
    RBW_INVALID_BUFFER_NAME,
    RBW_UNKNOWN
}RingBuffWrapperError_e;

RingBuffWrapperError_e RingBuffInitWrapped(RingBuffers_e nameOfBuff, uint8_t* buff, size_t size);
RingBuffWrapperError_e RingBuffPutWrapped(RingBuffers_e nameOfBuff, uint8_t data);
RingBuffWrapperError_e RingBuffGetWrapped(RingBuffers_e nameOfBuff, uint8_t* data);
bool RingBuffEmptyWrapped(RingBuffers_e nameOfBuff);

#endif