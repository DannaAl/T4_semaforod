/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v7.0
processor: MK66FN2M0xxx18
package_id: MK66FN2M0VMD18
mcu_data: ksdk2_0
processor_version: 0.7.9
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0}
  - {pin_num: E9, peripheral: UART0, signal: TX, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB16 (pin E10) is configured as UART0_RX */
    PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);

    /* PORTB17 (pin E9) is configured as UART0_TX */
    PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}


void BOARD_InitLEDsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTA11 (pin L9)  */
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, &LED_BLUE_config);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC9 (pin D7)  */
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE6 (pin E1)  */
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

    const port_pin_config_t LED_BLUE = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as PTA11 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTA11 (pin L9) is configured as PTA11 */
    PORT_SetPinConfig(BOARD_LED_BLUE_PORT, BOARD_LED_BLUE_PIN, &LED_BLUE);

    const port_pin_config_t LED_RED = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is disabled */
                                       kPORT_OpenDrainDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as PTC9 */
                                       kPORT_MuxAsGpio,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTC9 (pin D7) is configured as PTC9 */
    PORT_SetPinConfig(BOARD_LED_RED_PORT, BOARD_LED_RED_PIN, &LED_RED);

    const port_pin_config_t LED_GREEN = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as PTE6 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTE6 (pin E1) is configured as PTE6 */
    PORT_SetPinConfig(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, &LED_GREEN);
}


void BOARD_InitBUTTONsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA10 (pin M9)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD11 (pin B2)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    /* PORTA10 (pin M9) is configured as PTA10 */
    PORT_SetPinMux(BOARD_SW3_PORT, BOARD_SW3_PIN, kPORT_MuxAsGpio);

    /* Interrupt configuration on PORTA10 (pin M9): Interrupt on falling edge */
    PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, kPORT_InterruptFallingEdge);

    PORTA->PCR[10] = ((PORTA->PCR[10] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | (uint32_t)(kPORT_PullUp));

    /* PORTD11 (pin B2) is configured as PTD11 */
    PORT_SetPinMux(BOARD_SW2_PORT, BOARD_SW2_PIN, kPORT_MuxAsGpio);

    /* Interrupt configuration on PORTD11 (pin B2): Interrupt on falling edge */
    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, kPORT_InterruptFallingEdge);

    PORTD->PCR[11] = ((PORTD->PCR[11] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | (uint32_t)(kPORT_PullUp));
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
