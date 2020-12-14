/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-11-30 20:17:26
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-04 12:19:37
 * @FilePath     : \DAPLink\source\hic_hal\atmel\sam3u2c\user_spi.c
 */

#include "user_spi.h"

void SPI_IO_Init(void)
{
	MISO_RD_SET();
	MOSI_SET();
	CLK_SET();
	CS_SET();
	CS_H();
	CLK_L();
}
uint8_t SPI_W25Q_RW(uint8_t data)
{
	uint8_t r_data = 0;
	for(uint8_t i=0;i<8;i++)
    {   
        if (data & 0x80)
			MOSI_H();
		else
			MOSI_L();
        data <<= 1;
		CLK_L(); 
        CLK_H();
		r_data<<=1;
		if(MISO_RD())
		{
			r_data |= 0x1;
		}
    }
	MOSI_L();
	
    return r_data;
}
/**
 * @}
 */
