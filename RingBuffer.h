/**
 * @project
 * @file RingBuffer.h
 * @author Daniel Dunham (Daniel.Dunham1@assaabloy.com)
 * @brief Ring Buffer             Ring buffers for various data. Add to this as needed.
 * @version X.X.X
 * @date 2025-01-28
 * @copyright Copyright (c) 2025 Norton Rixson
 */
#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct RingBuff_t RingBuff_t;
typedef RingBuff_t* RingBuff_Handle_t;

typedef enum RingBuffErrors_e
{
    RB_NONE,
    RB_FULL,
    RB_EMPTY,
    RB_NODATA,
    RB_UNKNOWN
} RingBuffErrors_e;

RingBuff_Handle_t RingBuffInit(uint8_t* buff, size_t size);

void RingBuffFree(RingBuff_Handle_t buff);

void RingBuffRst(RingBuff_Handle_t buff);

RingBuffErrors_e RingBuffPut(RingBuff_Handle_t buff, uint8_t data);

RingBuffErrors_e RingBuffGet(RingBuff_Handle_t buff, uint8_t* data);

bool RingBuffEmpty(RingBuff_Handle_t buff);

bool RingBuffFull(RingBuff_Handle_t buff);

size_t RingBuffMaxSize(RingBuff_Handle_t buff);

size_t RingBuffCurrSize(RingBuff_Handle_t buff);

RingBuffErrors_e RingBuffPeek(RingBuff_Handle_t buff, uint8_t* data, uint32_t slot);

#endif