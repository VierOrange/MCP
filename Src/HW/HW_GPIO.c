//
// HW_GPIO.c
//

/// \file HW_GPIO.c
/// Definition aller GPIO-Registerbänke und der Helper-Funktion, zur Einstellung des GPIO-Modus.

#include <Compiler.h>
#include <Debug.h>

#include <HW_GPIO.h>

#define CNFx_MODEx    0xFU

RegisterBankGPIO volatile GPIOA __attribute__((at(0x40010800)));
RegisterBankGPIO volatile GPIOB __attribute__((at(0x40010C00)));
RegisterBankGPIO volatile GPIOC __attribute__((at(0x40011000)));
RegisterBankGPIO volatile GPIOD __attribute__((at(0x40011400))); 
RegisterBankGPIO volatile GPIOE __attribute__((at(0x40011800)));
RegisterBankGPIO volatile GPIOF __attribute__((at(0x40011C00)));
RegisterBankGPIO volatile GPIOG __attribute__((at(0x40012000)));

/// GPIO für Eingabe oder Ausgabe einstellen.
/// GPIO kann in unterschiedliocher Weise verwendet werden. Erstens für Input (default), zweitens für Output.
/// Außerdem muss zwischen Standard-I/O und Alternate-I/O unterschieden werden.
/// Bei Output gibt es zusätzlich die Varianten PP (push-pull) und OD (open-drain).
/// Bei Input kann man zudem pull-up/down-Widerstände aktivieren.
/// \param[in] rb verweist auf die zug. GPIO-Registerbank.
/// \param[in] pin ist die Pin-Nummer (0 bis 15).
/// \param[in] config sind die 4 Konfigurations-Bits (CFG + MODE), die zur Einstellung dieses einen Pins
/// verwendet werden sollen.
void ConfigureGPIO(RegisterBankGPIO volatile * const rb, unsigned const pin, WORD const config)
{
  unsigned offset;
  WORD volatile * control;

  // The pin number must be in 0 .. 15
  // The GPIO port must be from GPIOA to GPIOG (there are no others).
  
  ASSERT(pin < 16U);
  ASSERT(rb == &GPIOA || rb == &GPIOB ||rb == &GPIOC ||rb == &GPIOD ||rb == &GPIOE ||rb == &GPIOF ||rb == &GPIOG);
  
  if ( (offset = pin * 4U) >= 32U )
  {
    offset -= 32U;
    control = &rb->CRH;
  } else
    control = &rb->CRL;

  *control = (*control & ~(CNFx_MODEx << offset)) | ((config & CNFx_MODEx) << offset);

  if ( config == GPIO_I_PU || config == GPIO_I_PD )
  {
    WORD const Mask = 1U << pin;

    if ( (config & GPIO_I_pu) != 0U )
      rb->ODR |=  Mask;
    else
      rb->ODR &= ~Mask;
  }
}
void SetGPIOPin(RegisterBankGPIO volatile * rb, unsigned const pin)
{
  ASSERT(pin < 16U);
  ASSERT(rb == &GPIOA || rb == &GPIOB ||rb == &GPIOC ||rb == &GPIOD ||rb == &GPIOE ||rb == &GPIOF ||rb == &GPIOG);
	rb->ODR |= (1U<<pin);
}
void ClearGPIOPin(RegisterBankGPIO volatile * rb, unsigned const pin)
{
	ASSERT(pin < 16U);
  ASSERT(rb == &GPIOA || rb == &GPIOB ||rb == &GPIOC ||rb == &GPIOD ||rb == &GPIOE ||rb == &GPIOF ||rb == &GPIOG);
	rb->ODR &= ~(1U<<pin);
}
