#include "main.h"

void AppTestUartPoll(void){
	/*
		PA2 > USART2_TX
		PA3 > USART2_RX
		Polling ile
	*/
	
	/* UART gerceklemesi icin init etmemiz (oncul tanimlamamiz) gereken birimler */
	GPIO_InitTypeDef GPIO_InitStruct;
	UART_HandleTypeDef UART_InitStruct;
	
	/* Birimlerin CLK sinyallerini enable (aktif) etmemiz gerekiyor! */
	/* GPIO A portunun clock'unu aktiflestir */
	__HAL_RCC_USART2_CLK_ENABLE();
	/* USART 2 clock'unu aktiflestir */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	
	/*
    seçilen       >> USART 2 				 
    iletisim hizi >> 115200  					
    veri uzunlugu >> 8 bit   
    dur bit sayisi>> 1 tane  
    eslik biti    >> x
    modu          >> Full Duplex 
    Handshaking   >> x
    OverSampling  >> 16
	*/
  GPIO_InitStruct.Pin 			= GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode 			= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  GPIO_InitStruct.Pull 			= GPIO_PULLUP;
  GPIO_InitStruct.Speed 		= GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  UART_InitStruct.Instance 						= USART2;
  UART_InitStruct.Init.BaudRate 			= 115200;
  UART_InitStruct.Init.WordLength 		= UART_WORDLENGTH_8B;
  UART_InitStruct.Init.StopBits 			= UART_STOPBITS_1;
  UART_InitStruct.Init.Parity 				= UART_PARITY_NONE;
  UART_InitStruct.Init.Mode 					= UART_MODE_TX_RX;
  UART_InitStruct.Init.HwFlowCtl 			= UART_HWCONTROL_NONE;
  UART_InitStruct.Init.OverSampling 	= UART_OVERSAMPLING_16;

	HAL_UART_Init(&UART_InitStruct);

	int32_t sayici = 10;
	uint8_t veri   = 'A';
	/*
		Ekrana 10 kez A karakteri yazar ve programdan cikar!
	*/
  while(sayici--){
		HAL_UART_Transmit(&UART_InitStruct, &veri, 1, 0xFFFF);
	}
}
