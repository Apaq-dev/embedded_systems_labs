#include "usart.h"

/*
 * 	Vitesse 9600 Bauds
 * 	8 bits de donnees
 * 	1 bit d'arret
 * 	pas de parit/
 * 	mode interruption
 *
 * */
init_usart(){

	RCC->AHBENR 	|= RCC_AHBENR_GPIOAEN; // Active l'horloge du port A
	GPIOA->MODER 	&= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
	GPIOA->MODER 	|= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);
	GPIOA->OTYPER 	&= ~GPIO_OTYPER_OT_2; // Sortie Push-Pull pour PA2 (TX)
	GPIOA->OTYPER 	|= GPIO_OTYPER_OT_3; // Sortie Open-Drain pour PA3 (RX)
	GPIOA->PUPDR 	&= ~(GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3);
	GPIOA->PUPDR 	|= (GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0);
	GPIOA->OSPEEDR 	&= ~(GPIO_OSPEEDR_OSPEEDR2 | GPIO_OSPEEDR_OSPEEDR3);
	GPIOA->AFR[0] 	&= ~(GPIO_AFRL_AFRL2| GPIO_AFRL_AFRL3);
	GPIOA->AFR[0] 	|= ((((uint32_t) 0x01) << (4*2)) | (((uint32_t) 0x01) << (4*3)));
	RCC->APB1ENR 	|= RCC_APB1ENR_USART2EN; // Active l'horloge du USART2
	RCC->APB1RSTR 	|= RCC_APB1RSTR_USART2RST; // Place le USART2 en Reset
	RCC->APB1RSTR 	&= ~RCC_APB1RSTR_USART2RST; // Retire le Reset du USART2

	// Protocole : (8 bits), (Parité pair), (1 Stop bit), (9600 Baud)
	USART2->CR1 	&= ~(USART_CR1_OVER8);
	USART2->CR1     &=     ~(USART_CR1_PCE | USART_CR1_M);             // Set no parity and 8 bits of data
	USART2->CR2 	&= ~(USART_CR2_STOP);
	USART2->BRR 	= (uint16_t)(SYSTEM_CLOCK / USART2_BAUD_RATE);
	USART2->CR1 	|= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}
