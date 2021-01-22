//
// DrvSPI.h
//

/// \file DrvSPI.h
/// Funktionen zum Intitialisieren einer SPI-Periphery.

#if ! defined(guard_DRV_SPI_H)
#define guard_DRV_SPI_H

#include <Compiler.h>

/// Ergebnis-Code fuer SPI-Funktionen.

typedef enum
{
	spiSuccess = 0,
	spiCantSend,
	spiNoData
} SpiResultType;


//typedef struct
//{
//  WORD rccSpi;
//  WORD rccGpio;
//  unsigned sckPin; 
//  unsigned misoPin; 
//  unsigned mosiClock;
//  RegisterBankUSART volatile  * rbSpi;
//  RegisterBankGPIO volatile * rbGpio;
//  WORD irqNum;
//} SpiConfigType;
///

#define INIT_CONFIG(U, G, SCK, MISO, MOSI) { RCC_SPI ## U, RCC_GPIO ## G, SCK, MISO, MOSI, &SPI ## U, &GPIO ## G, NVIC_SPI ## U }


/// Initialisierung des SPI1.
/// Der SPI1 wird eingestellt auf 8 Datenbits
/// \param baudRate ist die einzustellende Baud-Rate.
/// \return Ergebnis-Code, \sa SpiResultType
SpiResultType InitSPI(unsigned preScale);
/// Senden eines einzelnen Zeichens/Datenbytes.
/// \param data ist das Datum, dass zu senden ist.
/// \return Ergebnis-Code, \sa SpiResultType
SpiResultType SpiSend(HWRD data);
/// Empfaengen eines einzelnen Zeichens/Datenbytes.
/// \param buffer ist der Lager, wo das Datum zu speichen ist.
/// \return Ergebnis-Code, \sa SpiResultType
SpiResultType SpiRev(HWRD * buffer);

void foo(BYTE const data);
void BeleutenEinSpaltenLED(WORD const data);
#endif
