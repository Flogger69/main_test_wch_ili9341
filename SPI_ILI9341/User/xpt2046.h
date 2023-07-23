/*
 * xpt2046.h
 */

#ifndef XPT2046_H_
#define XPT2046_H_


/* Includes ------------------------------------------------------------------*/
#include "ili9341.h"
#include "main.h"

/* Private defines -----------------------------------------------------------*/

//Set TOUCH Hardware Control and Frame lines


// Inform the SPI port you are using.
#define XPT2046_SPI_PORT	SPI2

#define XPT2046_XY_SWAP  		0
#define XPT2046_X_INV   		0
#define XPT2046_Y_INV   		0

#define XPT2046_Y_ADDR 			0x90
#define XPT2046_X_ADDR 			0xD0

#define XPT2046_HOR_RES     	240
#define XPT2046_VER_RES     	320
#define XPT2046_X_MIN       	113
#define XPT2046_X_MAX       	3982
#define XPT2046_Y_MIN			316
#define XPT2046_Y_MAX       	4025

#define XPT2046_AVG         	4

/* Pin connection*/
#define XPT2046_CS_GPIO_Port 	TOUCH_CS_GPIO_Port
#define XPT2046_CS_Pin 			TOUCH_CS_Pin
#define XPT2046_IRQ_GPIO_Port 	TOUCH_IRQ_GPIO_Port
#define XPT2046_IRQ_Pin 		TOUCH_IRQ_Pin

/* Basic operations */
#define XPT2046_CS_Low()        GPIO_WriteBit(GPIOB, TOUCH_CS_Pin, Bit_RESET); // CS_
//#define XPT2046_CS_Low()   		XPT2046_CS_GPIO_Port->BSR &= ~XPT2046_CS_Pin
#define XPT2046_CS_High()  		GPIO_WriteBit(GPIOB, TOUCH_CS_Pin, Bit_SET); // CS-

/*Variables*/



/* Functions*/
uint32_t XPT2046_Irq_Read(void);
void XPT2046_Init(void);
void XPT2046_Get_Touch_XY(volatile uint16_t* x_kor, volatile uint16_t* y_kor, uint8_t count_read);
void XPT2046_Corr(uint16_t * x, uint16_t * y);

#endif
