/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-15 18:33:12
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-04 14:33:57
 * @FilePath     : \DAPLink\source\hic_hal\atmel\sam3u2c\show.h
 */

#ifndef __SHOW_H
#define __SHOW_H
#include "compiler.h"
#include "stdint.h"

#define Line1_Begin 30
#define Line2_Begin 5
#define Line3_Begin 5
#define Line4_Begin 30
#define Line5_Begin 0

#define X_Begin 0
#define Y_Begin 47
#define Z_Begin 95

#define Line1_Begin1 0
#define Line2_Begin1 0
#define Line3_Begin1 40
#define Line4_Begin1 0
#define Line5_Begin1 0
#if OLED_0_96
#define Y0 0
#define Y1 Y0 + 12
#define Y2 Y1 + 12
#define Y3 Y2 + 12
#define Y4 Y3 + 12
#define Y5 Y4 + 12
#else
#define Y0 0
#define Y1 Y0 + 8
#define Y2 Y1 + 8
#define Y3 Y2 + 8
#define Y4 Y3 + 12
#define Y5 Y4 + 12
#endif
#define REVERSE(DATA, BIT) (DATA) ^ (1 << (BIT)) //��λȡ��
#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004
#define BIT3 0x0008
#define BIT4 0x0010
#define BIT5 0x0020
#define BIT6 0x0040
#define BIT7 0x0080
#define BIT8 0x0100
#define BIT9 0x0200
#define BIT10 0x0400
#define BIT11 0x0800

typedef struct 
{
	uint8_t windows;
	uint8_t mode;
}_Show;

extern _Show Show;
uint8_t Select_Mode(void);
void Menu_Show(void);
void Show_Duty(void);
void Select_Offline(void);
void Select_WL_MODE(void);
void Display_WL_MODE(void);
void Display_Offline(void);
#endif
