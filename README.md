# Door_slave_btlr
"""
Алгоритм работы:
0. Получение питания -> ожидание разрешающего сигнала на pc14 (должен поддерживаться постоянно для работы драйвера, в противном случае перезагрузка и ожидание);
1. Далее ждет начальную команду 0x7F 5 секунд;
2. Если начальная команда 0x7F не получена, то в п.3. Если начальная команда 0x7F получена -> обработка команд мастера, если команд нет 10 секунд, то в п.3;
3. Проверка флага наличия основной прошивки, если выставлен, то в п.4, либо попытка восстановления резервной прошивки, перезагрузка и далее в п.0;
4. Проверка наличия версии основной прошивки (выставляется в основной программе), если нет, то в п.5, если есть, то грузим основную прошивку;
5. Инкрементируем счетчик попыток загрузки основной прошивки, если количество меньше 3, то грузим основную прошивку, иначе в п.6;
6. Снятие флага наличия основной прошивки, далее в п.0;
'''
Основная прошивка должна прописывать по адресу #define FW_VERSION_ADDR ((uint16_t *)0x0801A802) версию текущей прошивки (uint32_t). Версия не может быть 0xFFFFFFFF;

Предполагаемая последовательность действий над бутлоадером:
  HOST_GET_VERSION = 0x01,
  HOST_ERASE = 0x43,
  HOST_WRITE_MEM = 0x31,
  HOST_GET_CHECKSUM = 0xA1,
  HOST_GO = 0x21,
Все действия можно делать по отдельности, но перед HOST_WRITE_MEM всегда должен быть HOST_ERASE.

Добавить в основную прошивку:

#define FW_VERSION_ADDR ((uint16_t *)0x0801A802) //Адрес версии прошивки во флеше
#define FW_VERSION_CLEARED 0xFFFFFFFF

uint16_t ReadFlash_HalfWord(uint16_t *addr); //Чтение полуслова:
uint8_t WriteFlash_HalfWord(uint16_t *addr, uint16_t HalfWord); //Запись полуслова

//Прописываем версию прошивки по адресу
if ((ReadFlash_HalfWord(FW_VERSION_ADDR) | (ReadFlash_HalfWord(FW_VERSION_ADDR+1) << 16)) == FW_VERSION_CLEARED)
{
  uint32_t FW_VER = 0xABCDFEFC; //Версия прошивки любая (uint32_t)
  WriteFlash_HalfWord(FW_VERSION_ADDR, (uint16_t)FW_VER);
  WriteFlash_HalfWord(FW_VERSION_ADDR+1, (uint16_t)(FW_VER>>16));
}

uint16_t ReadFlash_HalfWord(uint16_t *addr)
{
  return *addr;
}

uint8_t WriteFlash_HalfWord(uint16_t *addr, uint16_t HalfWord)
{
  uint8_t state = SUCCESS;

  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
  {
    WRITE_REG(FLASH->KEYR, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_KEY2);
  }
  
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET) state = ERROR;
  else
  {
    __disable_irq();
      while(FLASH->SR & FLASH_SR_BSY);
      if (FLASH->SR & FLASH_SR_EOP) SET_BIT(FLASH->SR, FLASH_SR_EOP);
      state = ((FLASH->SR & (FLASH_SR_WRPRTERR | FLASH_SR_PGERR)) | 
               (FLASH->OBR & FLASH_OBR_OPTERR)) ? ERROR : SUCCESS;

      if (state == SUCCESS)
      {
        SET_BIT(FLASH->CR, FLASH_CR_PG);

        *(__IO uint16_t*)addr = HalfWord;

        while(FLASH->SR & FLASH_SR_BSY);
        if (FLASH->SR & FLASH_SR_EOP) SET_BIT(FLASH->SR, FLASH_SR_EOP);
        CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
        state = ((FLASH->SR & (FLASH_SR_WRPRTERR | FLASH_SR_PGERR)) | 
                 (FLASH->OBR & FLASH_OBR_OPTERR)) ? ERROR : SUCCESS;
      }        

      SET_BIT(FLASH->SR, (FLASH_SR_WRPRTERR | FLASH_SR_PGERR));
      SET_BIT(FLASH->CR, FLASH_CR_LOCK);
      if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) == RESET) state = ERROR;
    __enable_irq();
  }

  return state;
}
