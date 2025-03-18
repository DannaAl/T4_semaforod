/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Tarea4_Sema.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MK66F18.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "NVIC.h"
#include "GPIO.h"


SemaphoreHandle_t xSemaphoreIncome;
SemaphoreHandle_t xSemaphoreLeave;


volatile int available_places = 10;


void vTaskIncome(void *pvParameters);
void vTaskLeave(void *pvParameters);
void vTaskLEDmanage(void *pvParameters);


void USER_SW2_IRQ(void);
void USER_SW3_IRQ(void);

int main(void) {

    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    board_clk_init();
    board_SW_init();
    board_LED_init();



    xSemaphoreIncome = xSemaphoreCreateCounting(10, 0);
    xSemaphoreLeave = xSemaphoreCreateCounting(10, 0);


    xTaskCreate(vTaskIncome, "Income", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vTaskLeave, "Leave", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vTaskLEDmanage, "LEDmanage", configMINIMAL_STACK_SIZE, NULL, 2, NULL);


    vTaskStartScheduler();

    for (;;);
    return 0;
}


void vTaskIncome(void *pvParameters) {
    for (;;) {
        if (xSemaphoreTake(xSemaphoreIncome, portMAX_DELAY) == pdTRUE) {
            if (available_places > 0) {
                available_places--;
            }
        }
    }
}


void vTaskLeave(void *pvParameters) {
    for (;;) {
        if (xSemaphoreTake(xSemaphoreLeave, portMAX_DELAY) == pdTRUE) {
            if (available_places < 10) {
                available_places++;
            }
        }
    }
}


void vTaskLEDmanage(void *pvParameters) {
    for (;;)
    {
        if (available_places >= 7)
        {
            GPIO_PinWrite(GPIOC, LED_RED_PIN, 1);
            GPIO_PinWrite(GPIOE, LED_GREEN_PIN, 0);
            GPIO_PinWrite(GPIOA, LED_BLUE_PIN, 1);
        } else if (available_places >= 1 && available_places <= 6) {
            GPIO_PinWrite(GPIOC, LED_RED_PIN, 0);
            GPIO_PinWrite(GPIOE, LED_GREEN_PIN, 0);
            GPIO_PinWrite(GPIOA, LED_BLUE_PIN, 1);
        } else if(available_places <= 0){
            GPIO_PinWrite(GPIOC, LED_RED_PIN, 0);
            GPIO_PinWrite(GPIOE, LED_GREEN_PIN, 1);
            GPIO_PinWrite(GPIOA, LED_BLUE_PIN, 1);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


void USER_SW2_IRQ(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (PORT_GetPinsInterruptFlags(PORTD) & (1 << SW2_PIN)) {
        xSemaphoreGiveFromISR(xSemaphoreLeave, &xHigherPriorityTaskWoken);
        PORT_ClearPinsInterruptFlags(PORTD, 1 << SW2_PIN);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void USER_SW3_IRQ(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (PORT_GetPinsInterruptFlags(PORTA) & (1 << SW3_PIN)) {
        xSemaphoreGiveFromISR(xSemaphoreIncome, &xHigherPriorityTaskWoken);
        PORT_ClearPinsInterruptFlags(PORTA, 1 << SW3_PIN);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void PORTD_IRQHandler(void) {
    USER_SW2_IRQ();
}


void PORTA_IRQHandler(void) {
    USER_SW3_IRQ();
}
