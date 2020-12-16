#ifndef __OLED_H
#define __OLED_H			  	 
#include "compiler.h"
#include "stdlib.h"
#include "stdint.h"
#include "oledfont.h"	  	    	
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

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
//-----------------OLED�˿ڶ���----------------  					   
#ifndef STM32F103xB
#define OLED_CS_GPIO		PIOB	
#define OLED_CS_Pin		    PIO_PB21

#define OLED_DC_GPIO		PIOB	
#define OLED_DC_Pin		    PIO_PB19

#define OLED_RST_GPIO		PIOB	
#define OLED_RST_Pin		PIO_PB20

#define OLED_SDA_GPIO		PIOB	
#define OLED_SDA_Pin		PIO_PB17

#define OLED_SCL_GPIO		PIOB	
#define OLED_SCL_Pin		PIO_PB18

#define OLED_CS_H   		OLED_CS_GPIO->PIO_SODR  = OLED_CS_Pin  //�ߵ�ƽ
#define OLED_CS_L   		OLED_CS_GPIO->PIO_CODR   = OLED_CS_Pin  //�͵�ƽ

#define OLED_DC_H   		OLED_DC_GPIO ->PIO_SODR  = OLED_DC_Pin  //�ߵ�ƽ
#define OLED_DC_L   		OLED_DC_GPIO ->PIO_CODR   = OLED_DC_Pin  //�͵�ƽ

#define OLED_RST_H   		OLED_RST_GPIO ->PIO_SODR = OLED_RST_Pin  //�ߵ�ƽ
#define OLED_RST_L   		OLED_RST_GPIO ->PIO_CODR  = OLED_RST_Pin  //�͵�ƽ

#define OLED_SDA_H   		OLED_SDA_GPIO ->PIO_SODR = OLED_SDA_Pin  //�ߵ�ƽ
#define OLED_SDA_L   		OLED_SDA_GPIO ->PIO_CODR  = OLED_SDA_Pin  //�͵�ƽ

#define OLED_SCL_H   		OLED_SCL_GPIO ->PIO_SODR = OLED_SCL_Pin  //�ߵ�ƽ
#define OLED_SCL_L   		OLED_SCL_GPIO ->PIO_CODR  = OLED_SCL_Pin  //�͵�ƽ

#else
#define OLED_CS_GPIO		GPIOB	
#define OLED_CS_Pin		    GPIO_PIN_0

#define OLED_DC_GPIO		GPIOB	
#define OLED_DC_Pin		    GPIO_PIN_1

#define OLED_RST_GPIO		GPIOB	
#define OLED_RST_Pin		GPIO_PIN_3

#define OLED_SDA_GPIO		GPIOB	
#define OLED_SDA_Pin		GPIO_PIN_4

#define OLED_SCL_GPIO		GPIOB	
#define OLED_SCL_Pin		GPIO_PIN_5

#define OLED_CS_H   		OLED_CS_GPIO ->BSRR  = OLED_CS_Pin  //�ߵ�ƽ
#define OLED_CS_L   		OLED_CS_GPIO ->BRR   = OLED_CS_Pin  //�͵�ƽ

#define OLED_DC_H   		OLED_DC_GPIO ->BSRR  = OLED_DC_Pin  //�ߵ�ƽ
#define OLED_DC_L   		OLED_DC_GPIO ->BRR   = OLED_DC_Pin  //�͵�ƽ

#define OLED_RST_H   		OLED_RST_GPIO ->BSRR = OLED_RST_Pin  //�ߵ�ƽ
#define OLED_RST_L   		OLED_RST_GPIO ->BRR  = OLED_RST_Pin  //�͵�ƽ

#define OLED_SDA_H   		OLED_SDA_GPIO ->BSRR = OLED_SDA_Pin  //�ߵ�ƽ
#define OLED_SDA_L   		OLED_SDA_GPIO ->BRR  = OLED_SDA_Pin  //�͵�ƽ

#define OLED_SCL_H   		OLED_SCL_GPIO ->BSRR = OLED_SCL_Pin  //�ߵ�ƽ
#define OLED_SCL_L   		OLED_SCL_GPIO ->BRR  = OLED_SCL_Pin  //�͵�ƽ

#endif
//-----------------OLED�˿ڶ���---------------- 
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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���
//OLED�����ú���

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
	 
