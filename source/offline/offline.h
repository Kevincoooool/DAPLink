/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:37:28
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-04 14:34:58
 * @FilePath     : \DAPLink\source\hic_hal\atmel\sam3u2c\offline.h
 */
#ifndef __OFFLINE_HID_H__
#define __OFFLINE_HID_H__
#include "compiler.h"
#include "stdint.h"
enum
{
	MODE_SET_NORMAL = 0,
	MODE_SET_ONLINE,
	MODE_SET_OFFLINE,
	MODE_SET_ALGO,
	MODE_SET_FILE,
	MODE_SET_WIRELESS,
	MODE_SET_TX,
	MODE_SET_RX,
};

enum
{
	SHOW_MENU = 0,
	SHOW_FLM,
	SHOW_BIN,
	SHOW_AUTO,
	SHOW_ONLINE,
	SHOW_OFFLINE,
	SHOW_WIRELESS,
	SHOW_WL_TX,
	SHOW_WL_RX,

};

void Display_BIN(void);
void Display_FLM(void);
uint8_t FLASH_SWD(uint8_t *File);
uint8_t usbd_hid_process_offline(void);
void Auto_Fash(void);
#endif  
