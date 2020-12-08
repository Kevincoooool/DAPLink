#ifndef __OLED_H
#define __OLED_H			  	 
#include "compiler.h"
#include "stdlib.h"
#include "stdint.h"
#include "oledfont.h"	  	    	
//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define OLED_0_96 0
#define OLED_0_91 1

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
//-----------------OLED端口定义----------------  					   

#define OLED_CS_GPIO		PIOB	
#define OLED_CS_Pin		    PIO_PB17

#define OLED_DC_GPIO		PIOB	
#define OLED_DC_Pin		    PIO_PB19

#define OLED_RST_GPIO		PIOB	
#define OLED_RST_Pin		PIO_PB18

#define OLED_SDA_GPIO		PIOB	
#define OLED_SDA_Pin		PIO_PB21

#define OLED_SCL_GPIO		PIOB	
#define OLED_SCL_Pin		PIO_PB20

#define OLED_CS_H   		OLED_CS_GPIO->PIO_SODR  = OLED_CS_Pin  //高电平
#define OLED_CS_L   		OLED_CS_GPIO->PIO_CODR   = OLED_CS_Pin  //低电平

#define OLED_DC_H   		OLED_DC_GPIO ->PIO_SODR  = OLED_DC_Pin  //高电平
#define OLED_DC_L   		OLED_DC_GPIO ->PIO_CODR   = OLED_DC_Pin  //低电平

#define OLED_RST_H   		OLED_RST_GPIO ->PIO_SODR = OLED_RST_Pin  //高电平
#define OLED_RST_L   		OLED_RST_GPIO ->PIO_CODR  = OLED_RST_Pin  //低电平

#define OLED_SDA_H   		OLED_SDA_GPIO ->PIO_SODR = OLED_SDA_Pin  //高电平
#define OLED_SDA_L   		OLED_SDA_GPIO ->PIO_CODR  = OLED_SDA_Pin  //低电平

#define OLED_SCL_H   		OLED_SCL_GPIO ->PIO_SODR = OLED_SCL_Pin  //高电平
#define OLED_SCL_L   		OLED_SCL_GPIO ->PIO_CODR  = OLED_SCL_Pin  //低电平
//-----------------OLED端口定义---------------- 
#define OLED_CS_Clr()   OLED_CS_L    //DC
#define OLED_CS_Set()   OLED_CS_H    //DC

#define OLED_DC_Clr()   OLED_DC_L    //DC
#define OLED_DC_Set()   OLED_DC_H    //DC

#define OLED_RST_Clr()  OLED_RST_L   //RST
#define OLED_RST_Set()  OLED_RST_H   //RST

#define OLED_SDIN_Clr() OLED_SDA_L   //SDA
#define OLED_SDIN_Set() OLED_SDA_H   //SDA

#define OLED_SCLK_Clr() OLED_SCL_L   //SCL
#define OLED_SCLK_Set() OLED_SCL_H   //SCL

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
//OLED控制用函数

#if OLED_0_96
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   				   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size,uint8_t mode);
void OLED_ShowCH(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_Show_CH(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_Show_CH_String(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size,uint8_t mode);
void OLED_Show_progress_bar(uint8_t temp,uint8_t chr_star,uint8_t chr_default,uint8_t x,uint8_t y,uint8_t size,uint8_t mode);
#else
void OLED_Refresh_Gram(void);
void OLED_ClearPoint(uint8_t x,uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_Init(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mode);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode);
void OLED_ShowChar6x8(uint8_t x,uint8_t y,uint8_t chr,uint8_t mode);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1,uint8_t mode);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1,uint8_t mode);
void OLED_Show_CH_String(uint8_t x, uint8_t y, const uint8_t *p, uint8_t size, uint8_t mode);
void OLED_Show_CH(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void OLED_ShowCH(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void OLED_ScrollDisplay(uint8_t num,uint8_t space,uint8_t mode);
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,uint8_t BMP[],uint8_t mode);
#endif
#endif  
	 
