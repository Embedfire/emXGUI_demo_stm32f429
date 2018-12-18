#ifndef __BOARD_H__
#define __BOARD_H__

/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/
/* STM32 �̼���ͷ�ļ� */
#include "stm32f4xx.h"

/* ������Ӳ��bspͷ�ļ� */
#include "./led/bsp_led.h" 
#include "./lcd/bsp_lcd.h"
#include "./lcd/dma2d_emxgui.h"
#include "./sdram/bsp_sdram.h" 
#include "./touch/bsp_i2c_touch.h"
#include "./touch/bsp_touch_gt9xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_spi_flash.h"
#include "./font/fonts.h"
#include "./Bsp/wm8978/bsp_wm8978.h"
#include "ff.h"
#include "FatFs_test.h"
#include "./camera/bsp_ov5640.h"
#include "./Bsp/systick/bsp_SysTick.h"

/*
*************************************************************************
*                               ��������
*************************************************************************
*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	

#endif /* __BOARD_H__ */