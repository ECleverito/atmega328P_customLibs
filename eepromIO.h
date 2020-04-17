#define EEPROM_PTR_L 1023
#define EEPROM_PTR_H 1022

#define EEPROM_SPTR_IL 0b11111110
#define EEPROM_SPTR_IH 0b11

void resetEEPROM_StackPtr();

uint16_t getEEPROM_StackPtr();

void incEEPROM_StackPtr();

void decEEPROM_StackPtr();

uint8_t EEPROM_read(uint16_t EEPROM_addr);

void EEPROM_write(uint16_t EEPROM_addr, uint8_t data);

