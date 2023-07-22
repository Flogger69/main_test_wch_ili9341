/*
 * main.h
 *
 *  Created on: May 2, 2023
 *      Author: vl
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "debug.h"


#define ILI9341_RES_Pin       GPIO_Pin_3 //
#define ILI9341_RES_GPIO_Port GPIOA
#define ILI9341_CS_Pin        GPIO_Pin_1
#define ILI9341_CS_GPIO_Port  GPIOA
#define ILI9341_DC_Pin        GPIO_Pin_2
#define ILI9341_DC_GPIO_Port  GPIOA

#define TOUCH_SCK_Pin GPIO_Pin_13			// CLCK SPI2
#define TOUCH_SCK_GPIO_Port GPIOB
#define TOUCH_IRQ_Pin GPIO_Pin_0			//IRQ TS Pin
#define TOUCH_IRQ_GPIO_Port GPIOB
#define TOUCH_CS_Pin GPIO_Pin_12         	// CS Pin
#define TOUCH_CS_GPIO_Port GPIOB
#define TOUCH_MISO_Pin GPIO_Pin_14			//MISO SPI2
#define TOUCH_MISO_GPIO_Port GPIOB
#define TOUCH_MOSI_Pin GPIO_Pin_15			//MOSI SPI2
#define TOUCH_MOSI_GPIO_Port GPIOB

#endif /* MAIN_H_ */
