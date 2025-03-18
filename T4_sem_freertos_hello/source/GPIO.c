/*
 * GPIO.c
 *
 *  Created on: 16 mar. 2025
 *      Author: danna
 */
#include "NVIC.h"
#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
void board_clk_init(void)
{
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortE);
}

void board_LED_init(void)
{
    PORT_SetPinMux(PORTC, LED_RED_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE, LED_GREEN_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTA, LED_BLUE_PIN, kPORT_MuxAsGpio);





    // Configuración de los LEDs como salidas
    gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 1};
    GPIO_PinInit(GPIOC, LED_RED_PIN, &led_config);
    GPIO_PinInit(GPIOE, LED_GREEN_PIN, &led_config);
    GPIO_PinInit(GPIOA, LED_BLUE_PIN, &led_config);


}


void board_SW_init(void)
{


    port_pin_config_t SW_config = {/* Internal pull-up resistor is enabled */
									kPORT_PullUp,
									/* Fast slew rate is configured */
									kPORT_FastSlewRate,
									/* Passive filter is disabled */
									kPORT_PassiveFilterEnable,
									/* Open drain is disabled */
									kPORT_OpenDrainDisable,
									/* Low drive strength is configured */
									kPORT_LowDriveStrength,
									/* Pin is configured as GPIO */
									kPORT_MuxAsGpio,
									/* Pin Control Register fields [15:0] are not locked */
									kPORT_UnlockRegister};

	NVIC_set_basepri_threshold(PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTA_IRQn,PRIORITY_4);
	NVIC_enable_interrupt_and_priotity(PORTD_IRQn,PRIORITY_4);
	NVIC_global_enable_interrupts;

    PORT_SetPinMux(PORTA, SW3_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, SW2_PIN, kPORT_MuxAsGpio);
    PORT_SetPinConfig(PORTA, SW3_PIN, &SW_config);
    PORT_SetPinConfig(PORTD, SW2_PIN, &SW_config);

    // Configuración de los botones como entradas con interrupciones
     gpio_pin_config_t sw_config = { kGPIO_DigitalInput, 1};
     GPIO_PinInit(GPIOD, SW2_PIN, &sw_config);
     GPIO_PinInit(GPIOA, SW3_PIN, &sw_config);

     PORT_SetPinInterruptConfig(PORTD, SW2_PIN, kPORT_InterruptFallingEdge);
     PORT_SetPinInterruptConfig(PORTA, SW3_PIN, kPORT_InterruptFallingEdge);

     EnableIRQ(PORTA_IRQn);
     EnableIRQ(PORTD_IRQn);


}
