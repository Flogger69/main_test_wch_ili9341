/*
 * xpt2046.c
 *
 *  Created on: Sep 5, 2021
 *      Author: paulo
 */
#include "main.h"
#include "xpt2046.h"

struct Disp{
	uint16_t xstart;
	uint16_t ystart;
	uint16_t width;
	uint16_t height;
	uint8_t rotation;
}Disp;

struct Touchpad1{
	uint16_t width;
	uint16_t height;
	uint16_t x_min;
	uint16_t x_max;
	uint16_t y_min;
	uint16_t y_max;
	uint8_t rotation;
	int16_t avg_buf_x[XPT2046_AVG];
	int16_t avg_buf_y[XPT2046_AVG];
	uint8_t avg_last;
}Touchpad1;
/**
 * TOUCH Select
 *
 * @param   void
 *
 * @return  void
 */

void XPT2046_Select(void)
{
	XPT2046_CS_Low();

}

/**
 * TOUCH Deselect
 *
 * @param   void
 *
 * @return  void
 */
void XPT2046_Deselect(void)
{

	XPT2046_CS_High();

}

uint32_t XPT2046_Irq_Read(void)
{
	return GPIO_ReadOutputDataBit(GPIOB, TOUCH_IRQ_Pin);

}

static uint8_t SendReceive_Byte(SPI_TypeDef *SPIx, uint8_t data)
{
	uint8_t Rx_data=0;
	SPI_I2S_SendData(SPI2, data);

	Rx_data = SPI_I2S_ReceiveData(SPI2);

    return Rx_data;
}

void XPT2046_Init(void)

{
	Touchpad1.width = 320 ;
	Touchpad1.height = 240 ;
	Touchpad1.rotation = 0;
	Touchpad1.x_min = XPT2046_X_MIN;
	Touchpad1.x_max = XPT2046_X_MAX;
	Touchpad1.y_min = XPT2046_Y_MIN;
	Touchpad1.y_max = XPT2046_Y_MAX;

	XPT2046_Select();
    SendReceive_Byte(SPI2, 0X80);
    SendReceive_Byte(SPI2, 0X00);
    SendReceive_Byte(SPI2, 0X00);
    Delay_Ms(1);
    XPT2046_Deselect();
}

uint16_t XPT2046_Get_Value(uint8_t address)
{
    uint16_t data = 0;
    XPT2046_Select();
    SendReceive_Byte(SPI2, address);
    data = SendReceive_Byte(SPI2, 0X00);
    data <<= 8;

    data |= SendReceive_Byte(SPI2, 0X00);
    data >>= 3;
    XPT2046_Deselect();
    return data;
}

void XPT2046_Get_Touch_XY(volatile uint16_t* x_kor, volatile uint16_t* y_kor, uint8_t count_read)
{
    uint8_t i = 0;
    uint16_t tmpx, tmpy, touch_x, touch_y = 0;

    touch_x = XPT2046_Get_Value(XPT2046_X_ADDR);
    touch_y = XPT2046_Get_Value(XPT2046_Y_ADDR);
    for (i = 0; i < count_read; i++)
    {
        tmpx = XPT2046_Get_Value(XPT2046_X_ADDR);
        tmpy = XPT2046_Get_Value(XPT2046_Y_ADDR);

        if (tmpx == 0)
        {
        	tmpy = 0;
        }
        else if (tmpy == 0)
        {
        	tmpx = 0;
        }
        else
		{
			touch_x = (touch_x + tmpx) / 2;
			touch_y = (touch_y + tmpy) / 2;
		}
	}
	*x_kor = touch_x;
	*y_kor = touch_y;
}

void XPT2046_Corr(uint16_t * x, uint16_t * y)
{
#if XPT2046_XY_SWAP 
    int16_t swap_tmp;
    swap_tmp = *x;
    *x = *y;
    *y = swap_tmp;
#endif

    if((*x) > Touchpad1.x_min )
    {
    	(*x) -= Touchpad1.x_min ;
    }
    else
    {
    	(*x) = 0;
    }

    if((*y) > Touchpad1.y_min)
    {
    	(*y) -= Touchpad1.y_min;
    }
    else
    {
    	(*y) = 0;
    }

    if(Touchpad1.rotation==0||Touchpad1.rotation==2)
	{
		(*x) = (uint32_t)((uint32_t)(*x) * Touchpad1.width) / (Touchpad1.x_max - Touchpad1.x_min );
		(*y) = (uint32_t)((uint32_t)(*y) * Touchpad1.height) / (Touchpad1.y_max - Touchpad1.y_min);
		(*x) =  Touchpad1.width - (*x);
		(*y) =  Touchpad1.height - (*y);
    }
    else
    {
		(*x) = (uint32_t)((uint32_t)(*x) * Touchpad1.height) / (Touchpad1.x_max - Touchpad1.x_min );
		(*y) = (uint32_t)((uint32_t)(*y) * Touchpad1.width) / (Touchpad1.y_max - Touchpad1.y_min);
    }



}

void XPT2046_Average(uint16_t * x, uint16_t * y)
{
    /*Shift out the oldest data*/
    uint8_t i;
    for(i = XPT2046_AVG - 1; i > 0 ; i--) {
        Touchpad1.avg_buf_x[i] = Touchpad1.avg_buf_x[i - 1];
        Touchpad1.avg_buf_y[i] = Touchpad1.avg_buf_y[i - 1];
    }

    /*Insert the new point*/
    Touchpad1.avg_buf_x[0] = *x;
    Touchpad1.avg_buf_y[0] = *y;
    if(Touchpad1.avg_last < XPT2046_AVG) Touchpad1.avg_last++;

    /*Sum the x and y coordinates*/
    int32_t x_sum = 0;
    int32_t y_sum = 0;
    for(i = 0; i < Touchpad1.avg_last ; i++) {
        x_sum += Touchpad1.avg_buf_x[i];
        y_sum += Touchpad1.avg_buf_y[i];
    }

    /*Normalize the sums*/
    (*x) = (int32_t)x_sum / Touchpad1.avg_last;
    (*y) = (int32_t)y_sum / Touchpad1.avg_last;
}


