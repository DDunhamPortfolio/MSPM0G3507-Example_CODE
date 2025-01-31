#include "ti/driverlib/dl_uart_main.h"
#include "UARTDriver.h"
#include "RingBufferWrapper.h"


#define MSPM0G3XXX true

volatile uint8_t RXDBG_RB_BASE[64];
volatile uint8_t TXDBG_RB_BASE[64];

void UARTFullInit(UART_Channel_e channelSelect)
{
    RingBuffWrapperError_e rb_ERR = RBW_UNKNOWN;
    switch(channelSelect)
    {
        case CH_DBG:
            NVIC_EnableIRQ(UART_DBG_INST_INT_IRQN);
            rb_ERR = RingBuffInitWrapped(UARTTX_DBG, TXDBG_RB_BASE, sizeof(TXDBG_RB_BASE));
            rb_ERR = RingBuffInitWrapped(UARTRX_DBG, RXDBG_RB_BASE, sizeof(RXDBG_RB_BASE));
            break;
        default:
            break;
    }
}

void UART_Text_TX(UART_Channel_e channelSelect, *data)
{
    uint8_t outputData;
    RingBuffWrapperError_e rb_ERR = RBW_UNKNOWN;
    switch(channelSelect)
    {
        case CH_DBG:
            while(!RingBuffEmptyWrapped(UARTTX_DBG))
            {
                rb_ERR = RingBuffGetWrapped(UARTTX_DBG, &outputData);
                DL_UART_Main_transmitData(UART_DBG_INST, outputData);
            }
            break;
        default:
            break;
    }
}

#if MSPM0G3XXX
void UART_DBG_INST_IRQHandler()
{
    RingBuffWrapperError_e  errorCheck = RBW_UNKNOWN;
    switch (DL_UART_Main_getPendingInterrupt(UART_DBG_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            errorCheck = RingBuffPutWrapped(UART_DBG, DL_UART_Main_receiveData(UART_DBG_INST));
            gCheckUART = true;
            break;
        default:
            break;
    }
}
#endif