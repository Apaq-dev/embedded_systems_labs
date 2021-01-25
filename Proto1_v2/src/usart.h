#ifndef USART_H
#define USART_H

#include "stm32f0xx.h"
#include "sys_def.h"

#define USART2_PRIORITY ((uint32_t) 0)

void init_usart(void);

#endif
