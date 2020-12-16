#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"
#include "gpio.h"
#include "cmsis_os2.h"
//#include "show.h"

uint8_t OLED_GRAM[144][4];
void OLED_Refresh_Gram(void)
{
	uint8_t i, n;
	for (i = 0; i < 4; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //����ҳ��ַ��0~7��
		OLED_WR_Byte(0x00, OLED_CMD);	  //������ʾλ�á��е͵�ַ
		OLED_WR_Byte(0x10, OLED_CMD);	  //������ʾλ�á��иߵ�ַ
		for (n = 0; n < 128; n++)
			OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
	}
}
//���Ժ���
void OLED_ColorTurn(uint8_t i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xA6, OLED_CMD); //������ʾ
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xA7, OLED_CMD); //��ɫ��ʾ
	}
}

//��Ļ��ת180��
void OLED_DisplayTurn(uint8_t i)
{
	if (i == 0)
	{
		OLED_WR_Byte(0xC8, OLED_CMD); //������ʾ
		OLED_WR_Byte(0xA1, OLED_CMD);
	}
	if (i == 1)
	{
		OLED_WR_Byte(0xC0, OLED_CMD); //��ת��ʾ
		OLED_WR_Byte(0xA0, OLED_CMD);
	}
}

void OLED_WR_Byte(uint8_t dat, uint8_t cmd)
{
	uint8_t i;
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	OLED_CS_Clr();
	for (i = 0; i < 8; i++)
	{
		OLED_SCLK_Clr();
		if (dat & 0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat <<= 1;
	}
	OLED_CS_Set();
	OLED_DC_Set();
}

//����OLED��ʾ
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
	OLED_WR_Byte(0x14, OLED_CMD); //������ɱ�
	OLED_WR_Byte(0xAF, OLED_CMD); //������Ļ
}

//�ر�OLED��ʾ
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D, OLED_CMD); //��ɱ�ʹ��
	OLED_WR_Byte(0x10, OLED_CMD); //�رյ�ɱ�
	OLED_WR_Byte(0xAE, OLED_CMD); //�ر���Ļ
}

//�����Դ浽OLED
void OLED_Refresh(void)
{
	uint8_t i, n;
	for (i = 0; i < 4; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //��������ʼ��ַ
		OLED_WR_Byte(0x00, OLED_CMD);	  //���õ�����ʼ��ַ
		OLED_WR_Byte(0x10, OLED_CMD);	  //���ø�����ʼ��ַ
		for (n = 0; n < 128; n++)
			OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
	}
}
//��������
void OLED_Clear(void)
{
	uint8_t i, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 0; n < 128; n++)
		{
			OLED_GRAM[n][i] = 0; //�����������
		}
	}
	OLED_Refresh(); //������ʾ
}

//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t)
{
	uint8_t i, m, n;
	i = y / 8;
	m = y % 8;
	n = 1 << m;
	if (t)
	{
		OLED_GRAM[x][i] |= n;
	}
	else
	{
		OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
		OLED_GRAM[x][i] |= n;
		OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
	}
}

//����
//x1,y1:�������
//x2,y2:��������
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)
{
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; //������������
	delta_y = y2 - y1;
	uRow = x1; //�����������
	uCol = y1;
	if (delta_x > 0)
		incx = 1; //���õ�������
	else if (delta_x == 0)
		incx = 0; //��ֱ��
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; //ˮƽ��
	else
	{
		incy = -1;
		delta_y = -delta_x;
	}
	if (delta_x > delta_y)
		distance = delta_x; //ѡȡ��������������
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++)
	{
		OLED_DrawPoint(uRow, uCol, mode); //����
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}
//x,y:Բ������
//r:Բ�İ뾶
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r)
{
	int a, b, num;
	a = 0;
	b = r;
	while (2 * b * b >= r * r)
	{
		OLED_DrawPoint(x + a, y - b, 1);
		OLED_DrawPoint(x - a, y - b, 1);
		OLED_DrawPoint(x - a, y + b, 1);
		OLED_DrawPoint(x + a, y + b, 1);

		OLED_DrawPoint(x + b, y + a, 1);
		OLED_DrawPoint(x + b, y - a, 1);
		OLED_DrawPoint(x - b, y - a, 1);
		OLED_DrawPoint(x - b, y + a, 1);

		a++;
		num = (a * a + b * b) - r * r; //���㻭�ĵ���Բ�ĵľ���
		if (num > 0)
		{
			b--;
			a--;
		}
	}
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size1:ѡ������ 6x8/6x12/8x16/12x24
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode)
{
	uint8_t i, m, temp, size2, chr1;
	uint8_t x0 = x, y0 = y;
	if (size1 == 8)
		size2 = 6;
	else
		size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr1 = chr - ' ';											   //����ƫ�ƺ��ֵ
	for (i = 0; i < size2; i++)
	{
		if (size1 == 8)
		{
			temp = asc2_0806[chr1][i];
		} //����0806����
		else if (size1 == 12)
		{
			temp = asc2_1206[chr1][i];
		} //����1206����
		else if (size1 == 16)
		{
			temp = asc2_1608[chr1][i];
		} //����1608����
		else if (size1 == 24)
		{
			temp = asc2_2412[chr1][i];
		} //����2412����
		else
			return;
		for (m = 0; m < 8; m++)
		{
			if (temp & 0x01)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp >>= 1;
			y++;
		}
		x++;
		if ((size1 != 8) && ((x - x0) == size1 / 2))
		{
			x = x0;
			y0 = y0 + 8;
		}
		y = y0;
	}
}

//��ʾ�ַ���
//x,y:�������
//size1:�����С
//*chr:�ַ�����ʼ��ַ
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode)
{
	while ((*chr >= ' ') && (*chr <= '~')) //�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_ShowChar(x, y, *chr, size1, mode);
		if (size1 == 8)
			x += 6;
		else
			x += size1 / 2;
		chr++;
	}
	OLED_Refresh();
}
//��ʾһ�������ַ�
void OLED_Show_CH_String(uint8_t x, uint8_t y, const uint8_t *p, uint8_t size, uint8_t mode)
{
	uint8_t temp, t, t1;
	uint8_t y0 = y;

	for (t = 0; t < size; t++)
	{
		temp = p[t]; //���������ֿ�
		for (t1 = 0; t1 < 8; t1++)
		{
			if (temp & 0x80)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp <<= 1;
			y++;
			if ((y - y0) == size)
			{
				y = y0;
				x++;
				break;
			}
		}
	}
	OLED_Refresh_Gram();
}

//m^n
uint32_t OLED_Pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while (n--)
	{
		result *= m;
	}
	return result;
}

//��ʾ����
//x,y :�������
//num :Ҫ��ʾ������
//len :���ֵ�λ��
//size:�����С
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowNumber(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / OLED_Pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size1 / 2) * t, y, ' ', size1, mode);
				continue;
			}
			else
				enshow = 1;
		}
		OLED_ShowChar(x + (size1 / 2) * t, y, temp + '0', size1, mode);
	}
	OLED_Refresh(); //������ʾ
}

//��ʾ����
//x,y:�������
//num:���ֶ�Ӧ�����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode)
{
	uint8_t m, temp;
	uint8_t x0 = x, y0 = y;
	uint16_t i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	for (i = 0; i < size3; i++)
	{
		if (size1 == 16)
		{
			temp = Hzk1[num][i];
		} //����16*16����
		else if (size1 == 24)
		{
			temp = Hzk2[num][i];
		} //����24*24����
		else if (size1 == 32)
		{
			temp = Hzk3[num][i];
		} //����32*32����
		else if (size1 == 64)
		{
			temp = Hzk4[num][i];
		} //����64*64����
		else
			return;
		for (m = 0; m < 8; m++)
		{
			if (temp & 0x01)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp >>= 1;
			y++;
		}
		x++;
		if ((x - x0) == size1)
		{
			x = x0;
			y0 = y0 + 8;
		}
		y = y0;
	}
}
//��ʾ����
void OLED_ShowCH(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode)
{
	uint8_t temp, t, t1;
	uint8_t y0 = y;

	for (t = 0; t < size; t++)
	{
		temp = oled_CH_1616[chr][t]; //���������ֿ�
		for (t1 = 0; t1 < 8; t1++)
		{
			if (temp & 0x80)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp <<= 1;
			y++;
			if ((y - y0) == size)
			{
				y = y0;
				x++;
				break;
			}
		}
	}
	OLED_Refresh_Gram();
}
//��ʾ���������ַ�
void OLED_Show_CH(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode)
{
	OLED_ShowCH(x, y, chr * 2, size, 1);
	OLED_ShowCH(x + size / 2, y, chr * 2 + 1, size, 1);
}
//num ��ʾ���ֵĸ���
//space ÿһ����ʾ�ļ��
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode)
{
	uint8_t i, n, t = 0, m = 0, r;
	while (1)
	{
		if (m == 0)
		{
			OLED_ShowChinese(128, 8, t, 16, mode); //д��һ�����ֱ�����OLED_GRAM[][]������
			t++;
		}
		if (t == num)
		{
			for (r = 0; r < 16 * space; r++) //��ʾ���
			{
				for (i = 1; i < 144; i++)
				{
					for (n = 0; n < 4; n++)
					{
						OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
					}
				}
				OLED_Refresh();
			}
			t = 0;
		}
		m++;
		if (m == 16)
		{
			m = 0;
		}
		for (i = 1; i < 144; i++) //ʵ������
		{
			for (n = 0; n < 4; n++)
			{
				OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
			}
		}
		OLED_Refresh();
	}
}

//x,y���������
//sizex,sizey,ͼƬ����
//BMP[]��Ҫд���ͼƬ����
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode)
{
	uint16_t j = 0;
	uint8_t i, n, temp, m;
	uint8_t x0 = x, y0 = y;
	sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
	for (n = 0; n < sizey; n++)
	{
		for (i = 0; i < sizex; i++)
		{
			temp = BMP[j];
			j++;
			for (m = 0; m < 8; m++)
			{
				if (temp & 0x01)
					OLED_DrawPoint(x, y, mode);
				else
					OLED_DrawPoint(x, y, !mode);
				temp >>= 1;
				y++;
			}
			x++;
			if ((x - x0) == sizex)
			{
				x = x0;
				y0 = y0 + 8;
			}
			y = y0;
		}
	}
}

//��ʼ��SSD1306
void OLED_Init(void)
{
	#ifndef STM32F103xB
	PIOB->PIO_IDR  =PIOB->PIO_PER  = PIOB->PIO_OER  =  PIO_PB17;
	PIOB->PIO_IDR  =PIOB->PIO_PER  = PIOB->PIO_OER  =  PIO_PB18;
	PIOB->PIO_IDR  =PIOB->PIO_PER  = PIOB->PIO_OER  =  PIO_PB19;
	PIOB->PIO_IDR  =PIOB->PIO_PER  = PIOB->PIO_OER  =  PIO_PB20;
	PIOB->PIO_IDR  =PIOB->PIO_PER  = PIOB->PIO_OER  =  PIO_PB21;
#else
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_AFIO_REMAP_SWJ_NOJTAG(); //����JTAG
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
	#endif
	OLED_RST_Set();
	osDelay(10);
	OLED_RST_Clr();
	osDelay(10);
	OLED_RST_Set();
	OLED_CS_L;
	OLED_WR_Byte(0xAE, OLED_CMD); /*display off*/
	OLED_WR_Byte(0x00, OLED_CMD); /*set lower column address*/
	OLED_WR_Byte(0x10, OLED_CMD); /*set higher column address*/
	OLED_WR_Byte(0x00, OLED_CMD); /*set display start line*/
	OLED_WR_Byte(0xB0, OLED_CMD); /*set page address*/
	OLED_WR_Byte(0x81, OLED_CMD); /*contract control*/
	OLED_WR_Byte(0xff, OLED_CMD); /*128*/
	OLED_WR_Byte(0xA1, OLED_CMD); /*set segment remap*/
	OLED_WR_Byte(0xA6, OLED_CMD); /*normal / reverse*/
	OLED_WR_Byte(0xA8, OLED_CMD); /*multiplex ratio*/
	OLED_WR_Byte(0x1F, OLED_CMD); /*duty = 1/32*/
	OLED_WR_Byte(0xC8, OLED_CMD); /*Com scan direction*/
	OLED_WR_Byte(0xD3, OLED_CMD); /*set display offset*/
	OLED_WR_Byte(0x00, OLED_CMD);
	OLED_WR_Byte(0xD5, OLED_CMD); /*set osc division*/
	OLED_WR_Byte(0x80, OLED_CMD);
	OLED_WR_Byte(0xD9, OLED_CMD); /*set pre-charge period*/
	OLED_WR_Byte(0x1f, OLED_CMD);
	OLED_WR_Byte(0xDA, OLED_CMD); /*set COM pins*/
	OLED_WR_Byte(0x00, OLED_CMD);
	OLED_WR_Byte(0xdb, OLED_CMD); /*set vcomh*/
	OLED_WR_Byte(0x40, OLED_CMD);
	OLED_WR_Byte(0x8d, OLED_CMD); /*set charge pump enable*/
	OLED_WR_Byte(0x14, OLED_CMD);
	OLED_Clear();
	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
}
