//
// RB_SPI
//

/// \file RB_SPI.h
/// Registerbank-Datentyp für SPI.

#ifndef __RB_SPI_H__
# define __RB_SPI_H__

# include <Compiler.h>

/// SPI register bank.
/// STM32F103 Serial Peripheral Interface (SPIx). See reference manual, chapter 23.
typedef struct __reg_bank_SPI
{
  WORD CR1;                                           ///< Control register 1.
  WORD CR2;                                           ///< Control register 2.
  WORD SR;                                            ///< Status register.
  union {
    BYTE asByte;
    HWRD asHwrd;
  } DR;                                               ///< Data register (wahlweise als Byte oder Halbwort).
  HWRD dontTouchMe;
  WORD CRCPR;                                         ///< CRC polynomial register.
  WORD RXCRCR;                                        ///< Rx CRC register.
  WORD TXCRCR;                                        ///< Tx CRC register.
  WORD I2SCFGR;                                       ///< I2S configuration register.
  WORD I2SPR;                                         ///< I2S prescaler register.
} RegisterBankSPI;

// CR1

# define INDX_SPI_CR1_CPHA      0                     // 1 = the second clock transition is the first data capture edge
# define MASK_SPI_CR1_CPHA      (1U << INDX_SPI_CR1_CPHA)     

# define INDX_SPI_CR1_CPOL      1                     // 1 = idle clock is high
# define MASK_SPI_CR1_CPOL      (1U << INDX_SPI_CR1_CPOL)

# define INDX_SPI_CR1_MSTR      2                     // SPI master mode 
# define MASK_SPI_CR1_MSTR      (1U << INDX_SPI_CR1_MSTR)

# define INDX_SPI_CR1_BR        3                     // baud rate control (bits 3..5)
# define MASK_SPI_CR1_BR_PRESCALER_2		(0U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_4		(1U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_8		(2U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_16		(3U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_32		(4U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_64		(5U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_128	(6U << INDX_SPI_CR1_BR)
# define MASK_SPI_CR1_BR_PRESCALER_256	(7U << INDX_SPI_CR1_BR)

# define INDX_SPI_CR1_SPE       6                     // SPI enable bit (1 = peripheral enabled)
# define MASK_SPI_CR1_SPE       (1U << INDX_SPI_CR1_SPE)

# define INDX_SPI_CR1_SSI       8
# define MASK_SPI_CR1_SSI       (1U << INDX_SPI_CR1_SSI)

# define INDX_SPI_CR1_SSM       9
# define MASK_SPI_CR1_SSM       (1U << INDX_SPI_CR1_SSM)

# define INDX_SPI_CR1_DFF       11 
# define MASK_SPI_CR1_DFF       (1U << INDX_SPI_CR1_DFF)

# define INDX_SPI_CR1_LSBFIRST  7 
# define MASK_SPI_CR1_LSBFIRST  (1U << INDX_SPI_CR1_LSBFIRST)

// CR2

# define INDX_SPI_CR2_SSOE      2
# define MASK_SPI_CR2_SSOE      (1U << INDX_SPI_CR2_SSOE)

# define INDX_SPI_CR2_TXEIE     7
# define MASK_SPI_CR2_TXEIE     (1U << INDX_SPI_CR2_TXEIE)

# define INDX_SPI_CR2_TXDMAEN   1
# define MASK_SPI_CR2_TXDMAEN   (1U << INDX_SPI_CR2_TXDMAEN)

// SR

# define INDX_SPI_SR_BSY        7
# define MASK_SPI_SR_BSY        (1U << INDX_SPI_SR_BSY)

# define INDX_SPI_SR_TXE        1
# define MASK_SPI_SR_TXE        (1U << INDX_SPI_SR_TXE)

# define INDX_SPI_SR_RXNE        0
# define MASK_SPI_SR_RXNE       (1U << INDX_SPI_SR_RXNE)
    
#endif



































