/**
 * @file main.c
 * @author Daniel Jay Dunham (dunhamdan11@gmail.com)
 * @brief 
 * @version X.X.X.X
 * @date 2025-01-20
 * @copyright Copyright (c) 2025 DUNHAM ART AUDIO AND DESIGN
 */

#include <ti/driverlib/m0p/dl_interrupt.h>
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timera.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti/driverlib/m0p/sysctl/dl_sysctl_mspm0g1x0x_g3x0x.h"
#include "ti_msp_dl_config.h"


#define MILLIS_TO_MICROS_CONV(INPUT) ((INPUT/2) * 1000)


volatile int timerCounter = 0;

/**
 * @brief main
 * @return none 
 */
int main(void)
{
    SYSCFG_DL_init();

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    //DL_SYSCTL_enableSleepOnExit();

    DL_TimerA_startCounter(TIMER_0_INST);

    while (1) {
        //__WFI();
        DL_SYSCTL_enableSleepOnExit();
        if(timerCounter >= MILLIS_TO_MICROS_CONV(100))
        {
            DL_GPIO_togglePins(LEDS_PORT, LEDS_LED_1_PIN);
            timerCounter = 0;
        }
        else 
        {
            /*DO NOTHING*/
        }
        __WFI();
        //delay_cycles(MILLIS_INPUT_CONV(500));
        //DL_GPIO_togglePins(LEDS_PORT, LEDS_LED_1_PIN);
    }
}

void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST)) 
    {
        case DL_TIMERA_IIDX_REPEAT_COUNT:
            ++timerCounter;
            DL_SYSCTL_disableSleepOnExit();
           break;
        default:
            break;
    }
}
