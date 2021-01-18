#include "Horloge.h"

void init_clock()
{
	//Selection of the HSE source.
	RCC->CR = (uint32_t)
			(
					RCC_CR_HSEON
					| RCC_CR_HSEBYP
					| RCC_CR_HSION
			);


	// Configuration of the system'IOs clocks.
	RCC->CFGR = (uint32_t)
			(
					RCC_CFGR_SW_PLL
					| RCC_CFGR_HPRE_0
					| RCC_CFGR_PPRE_0
					| RCC_CFGR_PLLSRC_HSE_PREDIV
					| RCC_CFGR_PLLMUL6
			);

	//Hard set the value to 0 even if it is the default value.
	RCC->CFGR2 = (uint32_t)
			(
					RCC_CFGR2_PREDIV_DIV1
			);

	//Activate the PLL after the configuration.
	RCC->CR |= (uint32_t)
			(
					RCC_CR_PLLON
			);

	//Wait until the PLL is ready.
	while (!(RCC->CR & ((uint32_t)  RCC_CR_PLLRDY)));

	//Notify that the system clock changed.
	SystemCoreClockUpdate();

}

