//
// DrvUSART.c
//
#include <Compiler.h>

#include <HW_RCC.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>

#include <DrvSPI.h>


SpiResultType InitSPI(unsigned const preScale)
{
	PeripheryEnable(RCC_GPIOA);
	PeripheryEnable(RCC_GPIOC);
	PeripheryEnable(RCC_SPI1);
	
	ConfigureGPIO(&GPIOA, 4U, GPIO_O_STD_PP_02MHZ);		///> CS
	ConfigureGPIO(&GPIOA, 11U, GPIO_O_STD_PP_02MHZ);
	ConfigureGPIO(&GPIOC, 4U, GPIO_O_STD_PP_02MHZ);
	
	ConfigureGPIO(&GPIOA, 5U, GPIO_O_ALT_PP_02MHZ);		///> SCLK
	ConfigureGPIO(&GPIOA, 6U, GPIO_O_ALT_PP_02MHZ);		///> MISO
	ConfigureGPIO(&GPIOA, 7U, GPIO_O_ALT_PP_02MHZ);		///> MOSI 
	
	SetGPIOPin(&GPIOA, 4U);
	//SetGPIOPin(&GPIOA, 5U);
	//SetGPIOPin(&GPIOA, 6U);
	//SetGPIOPin(&GPIOA, 7U);
	
	switch(preScale)
	{
		case 2:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_2;
			break;
		case 4:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_4;
			break;
		case 8:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_8;
			break;
		case 16:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_16;
			break;
		case 32:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_32;
			break;
		case 64:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_64;
			break;
		case 128:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_128;
			break;
		default:
			SPI1.CR1 |= MASK_SPI_CR1_BR_PRESCALER_256;
			break;
	}
	SPI1.CR1 |= MASK_SPI_CR1_LSBFIRST;
	SPI1.CR1 |= MASK_SPI_CR1_CPOL;
	//SPI1.CR1 |= MASK_SPI_CR1_CPHA;
	SPI1.CR1 |= MASK_SPI_CR1_DFF;
	SPI1.CR1 |= MASK_SPI_CR1_SSM;
	SPI1.CR1 |= MASK_SPI_CR1_SSI;
	
	SPI1.CR1 |= MASK_SPI_CR1_MSTR;
	
	SPI1.CR1 |= MASK_SPI_CR1_SPE;
	return spiSuccess;
	
}

SpiResultType SpiSend(HWRD const data)
{
  if ( (SPI1.SR & MASK_SPI_SR_TXE) != 0U )
  {
    SPI1.DR.asHwrd = data;
		while(!(SPI1.SR & MASK_SPI_SR_TXE));
		
		
		//ClearGPIOPin(&GPIOA, 4U);
		//SetGPIOPin(&GPIOA,4U);
		
    return spiSuccess;
  } else
    return spiCantSend;
}

SpiResultType SpiRev(HWRD * buffer)
{
  if ( (SPI1.SR & MASK_SPI_SR_RXNE) != 0U )
  {		
    *buffer = SPI1.DR.asHwrd;
		
    return spiSuccess;
  } else
    return spiNoData;
}

void foo(BYTE const data)
{
	while(SpiSend(data) == spiCantSend);
	if(SPI1.SR & MASK_SPI_SR_BSY == 0U)
	{
		SPI1.CR1 &= ~MASK_SPI_CR1_SPE;
	}
	ClearGPIOPin(&GPIOA, 4U);
	SetGPIOPin(&GPIOA,4U);
	
	SetGPIOPin(&GPIOA,11U);
	SetGPIOPin(&GPIOC,4U);
}

void BeleutenEinSpaltenLED(WORD const data)
{
	BYTE tmp;
	UINT32 i;
	for(i = 0; i < 32U; i += 8U)
	{
		tmp = 0U;
		tmp |= (data >> i);
		while(SpiSend(tmp) == spiCantSend);
	}
	if(SPI1.SR & MASK_SPI_SR_BSY == 0U)
	{
		SPI1.CR1 &= ~MASK_SPI_CR1_SPE;
	}
	ClearGPIOPin(&GPIOA, 4U);
	SetGPIOPin(&GPIOA,4U);
	
	SetGPIOPin(&GPIOA,11U);
	SetGPIOPin(&GPIOC,4U);
}
