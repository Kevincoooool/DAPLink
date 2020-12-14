#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#include "compiler.h"
#include "sam3u2c.h"

#define MISO_RD()     (PIOA->PIO_PDSR & PIO_PA13)
#define MOSI_H()      (PIOA->PIO_SODR = PIO_PA14)
#define MOSI_L()      (PIOA->PIO_CODR = PIO_PA14)

#define CLK_H()       (PIOA->PIO_SODR = PIO_PA15)
#define CLK_L()       (PIOA->PIO_CODR = PIO_PA15)

#define CS_H()        (PIOA->PIO_SODR = PIO_PA16)
#define CS_L()        (PIOA->PIO_CODR = PIO_PA16)

#define MISO_H()        (PIOA->PIO_SODR = PIO_PA13)
#define MISO_L()        (PIOA->PIO_CODR = PIO_PA13)


#define MISO_RD_SET() (PIOA->PIO_IER  =PIOA->PIO_PER  = PIOA->PIO_ODR  =  PIO_PA13)
#define MOSI_SET()    (PIOA->PIO_IDR  =PIOA->PIO_PER  = PIOA->PIO_OER  =  PIO_PA14)
#define CLK_SET()     (PIOA->PIO_IDR  =PIOA->PIO_PER  = PIOA->PIO_OER  =  PIO_PA15)
#define CS_SET()      (PIOA->PIO_IDR  =PIOA->PIO_PER  = PIOA->PIO_OER  =  PIO_PA16)

void SPI_IO_Init(void);
uint8_t SPI_W25Q_RW(uint8_t data);

#endif /* SPI_H_INCLUDED */
