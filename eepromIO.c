
#include <avr/io.h>

#include "eepromIO.h"

void resetEEPROM_StackPtr()
{
	EEPROM_write(EEPROM_PTR_L, EEPROM_SPTR_IL);
	EEPROM_write(EEPROM_PTR_H, EEPROM_SPTR_IH);
}

uint16_t getEEPROM_StackPtr()
{
	uint16_t addressPtr;
	
	addressPtr = EEPROM_read(EEPROM_PTR_L);
	addressPtr+= EEPROM_read(EEPROM_PTR_H)<<8;
	
	return addressPtr;
}

void incEEPROM_StackPtr()
{
	uint16_t addressPtr = getEEPROM_StackPtr();
	
	addressPtr++;
	
	EEPROM_write(EEPROM_PTR_L,(addressPtr & 0xFF));
	EEPROM_write(EEPROM_PTR_H,addressPtr>>8);
	
}

void decEEPROM_StackPtr()
{
	uint16_t addressPtr = getEEPROM_StackPtr();
	
	addressPtr--;
	
	EEPROM_write(EEPROM_PTR_L,(addressPtr & 0xFF));
	EEPROM_write(EEPROM_PTR_H,addressPtr>>8);
	
}

uint8_t EEPROM_read(uint16_t EEPROM_addr)
{
	while(EECR & _BV(EEPE))
	;
	
	EEAR = EEPROM_addr;
	EECR |= _BV(EERE);
	
	return EEDR;
}

void EEPROM_write(uint16_t EEPROM_addr, uint8_t data)
{
	
	while(EECR & _BV(EEPE))
	;
	
	EEDR = data;
	EEAR = EEPROM_addr;
	
	// EECR = _BV(EEMPE);
	EECR = 4;
	EECR |= _BV(EEPE);
	
}

