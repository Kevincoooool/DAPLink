
#include "show.h"
#include "ff.h"
#include "oled.h"
#include "offline.h"
#include "my_flash_blob.h"
_Show Show = {0, 0};
extern FIL fnew; /* file objects */
extern FILINFO FileInfo;
extern DIR DirInfo;
extern FATFS fs; /* Work area (file system object) for logical drives */
extern FRESULT Res;
extern UINT br, bw;			 /* File R/W count */
extern BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
extern char Name_Buffer[20][20];
uint8_t Select_file = 0;
extern uint8_t Select_algo;
extern uint8_t button_num;
extern uint8_t Need_Next;
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
uint8_t Select_Mode(void)
{
	static uint8_t choose = Y0;
	if (button_num == 1)
	{
		if (choose < 24)
			choose += 12;
		if (choose >= 24)
			choose = 24;
		OLED_ShowString(0, choose - 12, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		if (choose >= 12)
			choose -= 12;
		if (choose <= 0)
			choose = 0;
		OLED_ShowString(0, choose + 12, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		OLED_Clear();
		if (choose == 0)
		{

			Show.mode = MODE_SET_ONLINE;
			Show.windows = SHOW_ONLINE;
			for (uint8_t i = 0; i < 12; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y1, oled_CH0[i], 12, 1);
		}
		else if (choose == 12)
		{

			Show.mode = MODE_SET_OFFLINE;
			Show.windows = SHOW_OFFLINE;
			button_num = 0;
		}
		else if (choose == 24)
		{

			Show.mode = MODE_SET_WIRELESS;
			Show.windows = SHOW_WIRELESS;
			button_num = 0;
		}
		button_num = 0;
		return Show.mode;
	}
	button_num = 0;
	OLED_ShowString(0, choose, ">>", 12, 1);

	return MODE_SET_NORMAL;
}
//��ҳ�˵���ʾ
void Menu_Show(void)
{
	///////////////////////////////��һ��///////////////////////////////////
	//��ʾ
	//	OLED_Show_CH(20 + 00, 0, 0, 12, 1);
	//	OLED_Show_CH(20 + 12, 0, 1, 12, 1);
	//	OLED_Show_CH(20 + 24, 0, 2, 12, 1);
	//	OLED_Show_CH(20 + 36, 0, 3, 12, 1);
	//	OLED_Show_CH(20 + 48, 0, 4, 12, 1);
	//	OLED_Show_CH(20 + 60, 0, 5, 12, 1);
	//	OLED_Show_CH(20 + 72, 0, 6, 12, 1);
	//	OLED_Show_CH(20 + 84, 0, 7, 12, 1);
	//	OLED_ShowString(0, Y1, "================", 12, 1);
	///////////////////////////////������///////////////////////////////////
	//����ģʽ
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, 0, oled_CH0[i], 12, 1);
	///////////////////////////////������/////////////////////////////////
	//����ģʽ
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, 12, oled_CH1[i], 12, 1);
	///////////////////////////////������///////////////////////////////////
	//����ģʽ
//		for (uint8_t i = 0; i < 12; i++)
//			OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH2[i], 12, 1);
	OLED_Refresh(); //��ʼ��ʾ
}
//�ѻ���¼ģʽ��ʾ
void Display_Offline(void)
{
	///////////////////////////////��һ��///////////////////////////////////
	//�����㷨
	OLED_ShowNumber(0, Y0, 1, 1, 8, 1);
	OLED_ShowString(8, Y0, ".", 8, 1);
	OLED_ShowString(16, Y0, (uint8_t *)STM32_ALGO[Select_algo].name, 8, 1);
	///////////////////////////////�ڶ���///////////////////////////////////
	//�����ļ�
	OLED_ShowNumber(0, Y1, 2, 1, 8, 1);
	OLED_ShowString(8, Y1, ".", 8, 1);
	OLED_ShowString(16, Y1, (uint8_t *)Name_Buffer[Select_file], 8, 1);
	//	OLED_ShowNumber(0, Y1, 2, 1, 8,1);
	//	OLED_ShowString(8, Y1, ".", 8, 1);
	OLED_ShowString(30, Y2, (uint8_t *)"Start Flash", 8, 1);
	//	///////////////////////////////������/////////////////////////////////
	//	// ///����ģʽ
	//	// for (uint8_t i = 0; i < 12; i++)
	//	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH1[i], 12, 1);
	//	// ///////////////////////////////������///////////////////////////////////
	//	// for (uint8_t i = 0; i < 12; i++)
	//	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y4, oled_CH2[i], 12, 1);
	OLED_Refresh(); //��ʼ��ʾ
}
//����ģʽѡ��
void Display_WL_MODE(void)
{
	///////////////////////////////��һ��///////////////////////////////////
	//�����㷨
	OLED_ShowNumber(0, Y0, 1, 1, 12, 1);
	OLED_ShowString(8, Y0, ".", 12, 1);
	for (uint8_t i = 0; i < 10; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y0, oled_CH6[i], 12, 1);
	///////////////////////////////�ڶ���///////////////////////////////////
	//�����ļ�
	OLED_ShowNumber(0, 12, 2, 1, 12, 1);
	OLED_ShowString(8, 12, ".", 12, 1);
	for (uint8_t i = 0; i < 10; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, 12, oled_CH7[i], 12, 1);
	///////////////////////////////������/////////////////////////////////
	// ///����ģʽ
	// for (uint8_t i = 0; i < 12; i++)
	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH1[i], 12, 1);
	// ///////////////////////////////������///////////////////////////////////
	// for (uint8_t i = 0; i < 12; i++)
	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y4, oled_CH2[i], 12, 1);
	OLED_Refresh_Gram(); //��ʼ��ʾ
}

//ѡ������ģʽ�Ƿ��仹�ǽ���
void Select_WL_MODE(void)
{
	static uint8_t choose = Y0;
	OLED_ShowString(110, choose, "<<", 12, 1);
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= 12)
			choose = 12;
		OLED_ShowString(110, choose - 12, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		if (choose >= 12)
			choose -= 12;
		if (choose <= Y0)
			choose = Y0;
		OLED_ShowString(110, choose + 12, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		OLED_Clear();
		if (choose == Y0)
		{
			Show.windows = SHOW_WL_TX;
			Show.mode = MODE_SET_TX;
			for (uint8_t i = 0; i < 10; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH6[i], 12, 1);
		}
		else if (choose == 12)
		{
			Show.windows = SHOW_WL_RX;
			Show.mode = MODE_SET_RX;
			for (uint8_t i = 0; i < 10; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH7[i], 12, 1);
		}
	}

	button_num = 0;
}

