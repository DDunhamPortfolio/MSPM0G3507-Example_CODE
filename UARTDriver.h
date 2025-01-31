/**
 * @project
 * @file RingBuffer.h
 * @author Daniel Dunham (Daniel.Dunham1@assaabloy.com)
 * @brief Ring Buffer             Ring buffers for various data. Add to this as needed.
 * @version X.X.X
 * @date 2025-01-28
 * @copyright Copyright (c) 2025 Norton Rixson
 */
#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

typedef enum UART_Channel_e
{
    CH_DBG,
    CH_BUS,
    CH_RFI
}UART_Channel_e;


void UARTFullInit(UART_Channel_e);


#endif