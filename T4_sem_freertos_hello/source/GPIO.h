/*
 * GPIO.h
 *
 *  Created on: 16 mar. 2025
 *      Author: danna
 */

#ifndef GPIO_H_
#define GPIO_H_


#define SW2_PIN 11U
#define SW3_PIN 10U

#define LED_RED_PIN 9U
#define LED_GREEN_PIN 6U
#define LED_BLUE_PIN 11U



void board_clk_init(void);

void board_LED_init(void);

void board_SW_init(void);


#endif /* GPIO_H_ */
