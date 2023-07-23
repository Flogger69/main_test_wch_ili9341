/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "debug.h"
#include "ili9341.h"
#include "touchpad.h"
#include "../lvgl/lvgl.h"

/* Global typedef */

/* Global define */
/* Global Variable */
//uint32_t time=0;
//__IO uint32_t Counter;
//void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
/*
void lv_ex_led_1(void)
{
    //Create a LED and switch it OFF
    lv_obj_t * led1  = lv_led_create(lv_scr_act(), NULL);
    lv_obj_align(led1, NULL, LV_ALIGN_CENTER, -80, 0);
    lv_led_off(led1);

    //Copy the previous LED and set a brightness
    lv_obj_t * led2  = lv_led_create(lv_scr_act(), led1);
    lv_obj_align(led2, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_bright(led2, 190);

    //Copy the previous LED and switch it ON
    lv_obj_t * led3  = lv_led_create(lv_scr_act(), led1);
    lv_obj_align(led3, NULL, LV_ALIGN_CENTER, 80, 0);
    lv_led_on(led3);
}
*/

/*
static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t * date = lv_calendar_get_pressed_date(obj);
        if(date) {
            printf("Clicked date: %02d.%02d.%d\n", date->day, date->month, date->year);
        }
    }
}
*/
static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked\n");
    }
    else if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Toggled\n");
    }
}

void lv_ex_btn_1(void)
{
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Toggled");
}


void lv_ex_gauge_1(void)
{
    /*Describe the color for the needles*/
    static lv_color_t needle_colors[3];
    needle_colors[0] = LV_COLOR_BLUE;
    needle_colors[1] = LV_COLOR_ORANGE;
    needle_colors[2] = LV_COLOR_PURPLE;

    /*Create a gauge*/
    lv_obj_t * gauge1 = lv_gauge_create(lv_scr_act(), NULL);
    lv_gauge_set_needle_count(gauge1, 3, needle_colors);
    lv_obj_set_size(gauge1, 200, 200);
    lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 40, 0);

    /*Set the values*/
    lv_gauge_set_value(gauge1, 0, 50);
    lv_gauge_set_value(gauge1, 1, 20);
    lv_gauge_set_value(gauge1, 2, 30);
}

/**
 * Advanced button transition examples
 */

void lv_ex_calendar_1(void)
{
    lv_obj_t  * calendar = lv_calendar_create(lv_scr_act(), NULL);
    lv_obj_set_size(calendar, 235, 235);
    lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(calendar, event_handler);

    ///Make the date number smaller to be sure they fit into their area
    lv_obj_set_style_local_text_font(calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, lv_theme_get_font_small());

    //Set today's date
    lv_calendar_date_t today;
    today.year = 2023;
    today.month = 7;
    today.day = 23;

    lv_calendar_set_today_date(calendar, &today);
    lv_calendar_set_showed_date(calendar, &today);

    //Highlight a few days
    static lv_calendar_date_t highlighted_days[3];       //Only its pointer will be saved so should be static
    highlighted_days[0].year = 2023;
    highlighted_days[0].month = 10;
    highlighted_days[0].day = 6;

    highlighted_days[1].year = 2023;
    highlighted_days[1].month = 10;
    highlighted_days[1].day = 11;

    highlighted_days[2].year = 2023;
    highlighted_days[2].month = 11;
    highlighted_days[2].day = 22;

    lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);
}

void MCU_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;// | GPIO_Pin_5 | GPIO_Pin_7;CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
     SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
     SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

     SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
     SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
     SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
     SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
     SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
     SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
     //SPI_InitStructure.SPI_CRCPolynomial = 7;
     SPI_Init(SPI1, &SPI_InitStructure);

     SPI_Cmd(SPI1, ENABLE);

     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; //irq :
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);

     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);


     RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
      SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
      SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

      SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
      SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
      SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
      SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
      SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
      SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
      //SPI_InitStructure.SPI_CRCPolynomial = 7;
      SPI_Init(SPI2, &SPI_InitStructure);

      SPI_Cmd(SPI2, ENABLE);


}

int main(void)
{
	//u8 i = 0;


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
	printf("This is printf example\r\n");

	MCU_INIT();
	lv_init();
	my_tft_init();
	touchpad_init();
	//ILI9341_Init();

	//ILI9341_FillScreen(0x0000);
	//ILI9341_FillRect(20,20,290,70,0xF800);
	//ILI9341_WriteString(30, 30,"HELLO Font_16x26", Font_16x26, 0xffff,0);

	//lv_ex_keyboard_1();
	//lv_ex_calendar_1();
	//lv_ex_gauge_1();
	//lv_ex_arc_1();
	lv_ex_btn_1();
	//lv_task_handler();
	//Delay_Ms(3000);

	//lv_ex_led_1();
	//lv_task_handler();
	while(1)
    {
        Delay_Ms(5);
        //GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      lv_tick_inc(1);
      lv_task_handler();
	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	u8 i = 0;
  while (1)
  {


	GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    Delay_Ms(100);

  }

  /* USER CODE END Error_Handler_Debug */
}

