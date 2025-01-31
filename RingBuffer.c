/**
 * @project
 * @file RingBuffer.c
 * @author Daniel Dunham (Daniel.Dunham1@assaabloy.com)
 * @brief Ring Buffer             Ring buffers for various data. Add to this as needed.
 * @version X.X.X
 * @date 2025-01-28
 * @copyright Copyright (c) 2025 Norton Rixson
 */

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "RingBuffer.h"

struct RingBuff_t{
    uint8_t* buffer;
    size_t head;
    size_t tail;
    size_t max;
    bool full;
};

/**
 * @brief    {brief}             Advance the head or tail
 * @param    val                 Current Position In Buffer
 * @param    max                 Max Size of Buffer
 * @return   {return}            Return Current Position
 */
static inline size_t AdvHeadTailVal(size_t val, size_t max)
{
    if(++val == max)
    {
        val = 0;
    }
    else 
    {
        /* DO NOTHING */
    }
    return val;
}

/**
 * @brief    {brief}             Advance the head pointer
 * @param    buff                Pointer to ring buffer.
 */
static void AdvHeadPtr(RingBuff_Handle_t buff)
{
    assert(buff);

    if(RingBuffFull(buff))
    {
        buff->tail = AdvHeadTailVal(buff->tail, buff->max);
    }
    else 
    {
        /* DO NOTHING */
    }

    buff->head = AdvHeadTailVal(buff->head, buff->max);
    buff->full = (buff->head == buff->tail);
}

/**
 * @brief    {brief}             Initialize Ring Buffer
 * @param    buff                Pointer to array that Ringbuffer is using.
 * @param    size                Size of ring Buffer.
 * @return   {return}            Pointer to Ring Buffer Handle.
 */
RingBuff_Handle_t RingBuffInit(uint8_t* buff, size_t size)
{
    assert(buff && size);

    RingBuff_Handle_t rBuff = malloc(sizeof(RingBuff_t));
    assert(rBuff);

    rBuff->buffer = buff;
    rBuff->max = size;
    RingBuffRst(rBuff);
    assert(RingBuffEmpty(rBuff));

    return rBuff;
}

/**
 * @brief    {brief}             Clear Ring buffer
 * @param    buff                Ring buffer to clear.
 */
void RingBuffFree(RingBuff_Handle_t buff)
{
    assert(buff);
    free(buff);
}

/**
 * @brief    {brief}             Ring Buffer Reset
 * @param    buff                Ring Buffer to Reset
 */
void RingBuffRst(RingBuff_Handle_t buff)
{
    //assert(buff);
    buff->head = 0;
    buff->tail = 0;
    buff->full = false;
}

/**
 * @brief    {brief}             Get current length of ring buffer.
 * @param    buff                Ring buffer
 * @return   {return}            Current length of ring buffer. 
 */
size_t RingBuffCurrSize(RingBuff_Handle_t buff)
{
    //assert(buff);

    size_t size = buff->max;
    if(!RingBuffFull(buff))
    {
        if(buff->head >= buff->tail)
        {
            size = buff->head - buff->tail;
        }
        else 
        {
            size = buff->max + buff->head - buff->tail;
        }
    }
    else 
    {
        /* DO NOTHING */
    }
    return size;
}

/**
 * @brief    {brief}             Get maximum length of ring buffer.
 * @param    buff                Ring buffer
 * @return   {return}            Maximum length of ring buffer. 
 */
size_t RingBuffMaxSize(RingBuff_Handle_t buff)
{
    assert(buff);
    return buff->max;
}

/**
 * @brief    {brief}             Enter data into ring buffer.
 * @param    buff                Ring buffer
 * @param    data                Data to enter.
 * @return   {return}            Error code.
 */
RingBuffErrors_e RingBuffPut(RingBuff_Handle_t buff, uint8_t data)
{
    RingBuffErrors_e error = RB_UNKNOWN;
    //assert(buff && buff->buffer);
    if(!RingBuffFull(buff))
    {
        buff->buffer[buff->head] = data;
        AdvHeadPtr(buff);
        error = RB_NONE;
    }
    else 
    {
        error = RB_FULL;
    }

    return error;
}

/**
 * @brief    {brief}             Get data from ring buffer. Alows data to be overwitten when read by moving head and tail pointers.
 * @param    buff                Ring buffer
 * @param    data                Pointer to data bucket.
 * @return   {return}            Error code.
 */
RingBuffErrors_e RingBuffGet(RingBuff_Handle_t buff, uint8_t* data)
{
    RingBuffErrors_e error = RB_UNKNOWN;
    assert(buff && buff->buffer);
    if(!RingBuffEmpty(buff))
    {
        *data = buff->buffer[buff->tail];
        buff->tail = AdvHeadTailVal(buff->tail, buff->max);
        buff->full = false;
        error = RB_NONE;
    }
    else 
    {
        error = RB_EMPTY;
    }
    return error;
}

/**
 * @brief    {brief}            Check if buffer is empty.
 * @param    buff               Ring buffer to check.
 * @return   true               Ring buffer is empty.
 * @return   false              Ring buffer is not empty.
 */
bool RingBuffEmpty(RingBuff_Handle_t buff)
{
    assert(buff);
    return(!RingBuffFull(buff) && (buff->head == buff->tail));
}

/**
 * @brief    {brief}            Check if buffer is full.
 * @param    buff               Ring buffer to check.
 * @return   true               Ring buffer is full.
 * @return   false              Ring buffer is not full.
 */
bool RingBuffFull(RingBuff_Handle_t buff)
{
    assert(buff);

    return (buff->full);
}

/**
 * @brief    {brief}             Look at ring buffer data without removing it.
 * @param    buff                Ring buffer to read.
 * @param    data                Pointer to data bucket.
 * @param    slot                Spot to read ring buffer up to.
 * @return   {return}            Ring buffer errors.
 */
RingBuffErrors_e RingBuffPeek(RingBuff_Handle_t buff, uint8_t *data, uint32_t slot)
{
    RingBuffErrors_e error = RB_UNKNOWN;
    size_t position;

    assert(buff && data && buff->buffer);
    
    if(RingBuffEmpty(buff) || slot > RingBuffCurrSize(buff))
    {
        error = RB_NODATA;
    }
    else 
    {
        /* DO NOTHING */
    }

    position = buff->tail;
    for(uint32_t i = 0; i < slot; ++i)
    {
        data[i] = buff->buffer[position];
        position = AdvHeadTailVal(position, buff->max);
        error = RB_NONE;
    }

    return error;
    
}