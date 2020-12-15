/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-15 14:27:56
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-04 11:58:13
 * @FilePath     : \DAPLink\source\hic_hal\atmel\sam3u2c\w25qxx.c
 */
#include "w25qxx.h"
#ifndef STM32F103xB
#include "user_spi.h"


#else
#include "bsp_spi.h"

#define SPI_IO_Init  DAP_SPI_Init
#define SPI_W25Q_RW  SPI_RW_2
#define CS_L() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define CS_H() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#endif
#include "uart.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//W25Q64 ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

uint16_t W25QXX_TYPE = W25Q128; //Ĭ����W25Q128

//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25Q128
//����Ϊ16M�ֽ�,����128��Block,4096��Sector

uint8_t W25QXX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	SPI_IO_Init(); //��ʼ��SPI
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	W25QXX_TYPE = W25QXX_ReadID(); //��ȡFLASH ID.
	if (W25QXX_TYPE != 0xff)
		return 0;
	else
		return 1;
}

//��ȡW25QXX��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
uint8_t W25QXX_ReadSR(void)
{
	uint8_t byte = 0;
	CS_L();			  //ʹ������
	SPI_W25Q_RW(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ�������
	byte = SPI_W25Q_RW(0Xff);		  //��ȡһ���ֽ�
	CS_H();				  //ȡ��Ƭѡ
	return byte;
}
//дW25QXX״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void W25QXX_Write_SR(uint8_t sr)
{
	CS_L();			   //ʹ������
	SPI_W25Q_RW(W25X_WriteStatusReg); //����дȡ״̬�Ĵ�������
	SPI_W25Q_RW(sr);				   //д��һ���ֽ�
	CS_H();				   //ȡ��Ƭѡ
}
//W25QXXдʹ��
//��WEL��λ
void W25QXX_Write_Enable(void)
{
	CS_L();			//ʹ������
	SPI_W25Q_RW(W25X_WriteEnable); //����дʹ��
	CS_H();				//ȡ��Ƭѡ
}
//W25QXXд��ֹ
//��WEL����
void W25QXX_Write_Disable(void)
{
	CS_L();			 //ʹ������
	SPI_W25Q_RW(W25X_WriteDisable); //����д��ָֹ��
	CS_H();				 //ȡ��Ƭѡ
}
//��ȡоƬID
//����ֵ����:
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128
uint16_t W25QXX_ReadID(void)
{
	uint16_t Temp = 0;
	CS_L();
	SPI_W25Q_RW(0x90); //���Ͷ�ȡID����
	SPI_W25Q_RW(0x00);
	SPI_W25Q_RW(0x00);
	SPI_W25Q_RW(0x00);
	Temp |= SPI_W25Q_RW(0xFF) << 8;
	Temp |= SPI_W25Q_RW(0xFF);
	CS_H();
	return Temp;
}
//��ȡSPI FLASH
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	uint16_t i;
	CS_L();					   //ʹ������
	SPI_W25Q_RW(W25X_ReadData);			   //���Ͷ�ȡ����
	SPI_W25Q_RW((uint8_t)((ReadAddr) >> 16)); //����24bit��ַ
	SPI_W25Q_RW((uint8_t)((ReadAddr) >> 8));
	SPI_W25Q_RW((uint8_t)ReadAddr);
	for (i = 0; i < NumByteToRead; i++)
	{
		pBuffer[i] = SPI_W25Q_RW(0XFF); //ѭ������
	}
	CS_H();
}
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
void W25QXX_Write_Page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint16_t i;
	W25QXX_Write_Enable();					//SET WEL
	CS_L();						//ʹ������
	SPI_W25Q_RW(W25X_PageProgram);				//����дҳ����
	SPI_W25Q_RW((uint8_t)((WriteAddr) >> 16)); //����24bit��ַ
	SPI_W25Q_RW((uint8_t)((WriteAddr) >> 8));
	SPI_W25Q_RW((uint8_t)WriteAddr);
	for (i = 0; i < NumByteToWrite; i++)
		SPI_W25Q_RW(pBuffer[i]); //ѭ��д��
	CS_H();			  //ȡ��Ƭѡ
	W25QXX_Wait_Busy();		  //�ȴ�д�����
}
//�޼���дSPI FLASH
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ����
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25QXX_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint16_t pageremain;
	pageremain = 256 - WriteAddr % 256; //��ҳʣ����ֽ���
	if (NumByteToWrite <= pageremain)
		pageremain = NumByteToWrite; //������256���ֽ�
	while (1)
	{
		W25QXX_Write_Page(pBuffer, WriteAddr, pageremain);
		if (NumByteToWrite == pageremain)
			break; //д�������
		else	   //NumByteToWrite>pageremain
		{
			pBuffer += pageremain;
			WriteAddr += pageremain;

			NumByteToWrite -= pageremain; //��ȥ�Ѿ�д���˵��ֽ���
			if (NumByteToWrite > 256)
				pageremain = 256; //һ�ο���д��256���ֽ�
			else
				pageremain = NumByteToWrite; //����256���ֽ���
		}
	};
}
//дSPI FLASH
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)

void W25QXX_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t W25QXX_BUFFER[4096];
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;
	uint16_t i;
	uint8_t *W25QXX_BUF;
	W25QXX_BUF = W25QXX_BUFFER;
	secpos = WriteAddr / 4096; //������ַ
	secoff = WriteAddr % 4096; //�������ڵ�ƫ��
	secremain = 4096 - secoff; //����ʣ��ռ��С
	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
	if (NumByteToWrite <= secremain)
		secremain = NumByteToWrite; //������4096���ֽ�
	while (1)
	{
		W25QXX_Read(W25QXX_BUF, secpos * 4096, 4096); //������������������
		for (i = 0; i < secremain; i++)				  //У������
		{
			if (W25QXX_BUF[secoff + i] != 0XFF)
				break; //��Ҫ����
		}
		if (i < secremain) //��Ҫ����
		{
			W25QXX_Erase_Sector(secpos);	//�����������
			for (i = 0; i < secremain; i++) //����
			{
				W25QXX_BUF[i + secoff] = pBuffer[i];
			}
			W25QXX_Write_NoCheck(W25QXX_BUF, secpos * 4096, 4096); //д����������
		}
		else
			W25QXX_Write_NoCheck(pBuffer, WriteAddr, secremain); //д�Ѿ������˵�,ֱ��д������ʣ������.
		if (NumByteToWrite == secremain)
			break; //д�������
		else	   //д��δ����
		{
			secpos++;	//������ַ��1
			secoff = 0; //ƫ��λ��Ϊ0

			pBuffer += secremain;		 //ָ��ƫ��
			WriteAddr += secremain;		 //д��ַƫ��
			NumByteToWrite -= secremain; //�ֽ����ݼ�
			if (NumByteToWrite > 4096)
				secremain = 4096; //��һ����������д����
			else
				secremain = NumByteToWrite; //��һ����������д����
		}
	};
}
//��������оƬ
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)
{
	W25QXX_Write_Enable(); //SET WEL
	W25QXX_Wait_Busy();
	CS_L();		  //ʹ������
	SPI_W25Q_RW(W25X_ChipErase); //����Ƭ��������
	CS_H();			  //ȡ��Ƭѡ
	W25QXX_Wait_Busy();		  //�ȴ�оƬ��������
}
//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ��ɽ��������ʱ��:150ms
void W25QXX_Erase_Sector(uint32_t Dst_Addr)
{
	//����falsh�������,������
	//	printf("fe:%x\r\n", Dst_Addr);
	Dst_Addr *= 4096;
	W25QXX_Write_Enable(); //SET WEL
	W25QXX_Wait_Busy();
	CS_L();					   //ʹ������
	SPI_W25Q_RW(W25X_SectorErase);			   //������������ָ��
	SPI_W25Q_RW((uint8_t)((Dst_Addr) >> 16)); //����24bit��ַ
	SPI_W25Q_RW((uint8_t)((Dst_Addr) >> 8));
	SPI_W25Q_RW((uint8_t)Dst_Addr);
	CS_H();		//ȡ��Ƭѡ
	W25QXX_Wait_Busy(); //�ȴ��������
}
//�ȴ�����
void W25QXX_Wait_Busy(void)
{
	while ((W25QXX_ReadSR() & 0x01) == 0x01)
		; // �ȴ�BUSYλ���
}
//�������ģʽ
void W25QXX_PowerDown(void)
{
	CS_L();		  //ʹ������
	SPI_W25Q_RW(W25X_PowerDown); //���͵�������
	CS_H();			  //ȡ��Ƭѡ
							  //	delay_us(3);			//�ȴ�TPD
}
//����
void W25QXX_WAKEUP(void)
{
	CS_L();				 //ʹ������
	SPI_W25Q_RW(W25X_ReleasePowerDown); //  send W25X_PowerDown command 0xAB
	CS_H();					 //ȡ��Ƭѡ
									 //	delay_us(3);				   //�ȴ�TRES1
}
