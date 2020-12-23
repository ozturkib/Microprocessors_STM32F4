#include "main.h"

/* Bir bitlik veriyi saklamak icin ulasan diye degisken olusturdum*/
uint8_t ulasan;
uint8_t basarili[] = "BASARILIDIR.";

UART_HandleTypeDef UART_InitStruct;

/* UART2 Interrupt Service Routine */
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UART_InitStruct);
}

/* Buradaki callback belirtilen adette byte ulastiginda HAL_UART_IRQHandler tarafindan cagrilir! */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/*
		Buradaki alt kontrol USART2 icin sadece aktiftir ve
		Her girilen karakteri echo yaparak, transmit > receive
		Ayni zamanda buyuk A girildiginde ekrana ilave olarak BASARILIDIR yazar!
	*/
  if (huart->Instance == USART2)
  {
    /* 100ms timeout ile 1 byte yolla */
    HAL_UART_Transmit(huart, &ulasan, 1, 100);
		
    /* Kesme modunda ulasan 1 byte alma */ 
    HAL_UART_Receive_IT(huart, &ulasan, 1);
		
		if(ulasan == 'A')
				HAL_UART_Transmit(huart, basarili, sizeof(basarili), HAL_MAX_DELAY);
  }
}

void AppTestUartInterrupt(void){
	/*
		PA2 > USART2_TX
		PA3 > USART2_RX
		Interrupt ile
	*/
	
	/* UART gerceklemesi icin init etmemiz (oncul tanimlamamiz) gereken birimler */
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* Birimlerin CLK sinyallerini enable (aktif) etmemiz gerekiyor! */
	/* GPIO A portunun clock'unu aktiflestir */
	__HAL_RCC_USART2_CLK_ENABLE();
	/* USART 2 clock'unu aktiflestir */
	__HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin 			= GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode 			= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  GPIO_InitStruct.Pull 			= GPIO_PULLUP;
  GPIO_InitStruct.Speed 		= GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
  UART_InitStruct.Instance 						= USART2;
  UART_InitStruct.Init.BaudRate 			= 115200;
  UART_InitStruct.Init.WordLength 		= UART_WORDLENGTH_8B;
  UART_InitStruct.Init.StopBits 			= UART_STOPBITS_1;
  UART_InitStruct.Init.Parity 				= UART_PARITY_NONE;
  UART_InitStruct.Init.Mode 					= UART_MODE_TX_RX;
  UART_InitStruct.Init.HwFlowCtl 			= UART_HWCONTROL_NONE;
  UART_InitStruct.Init.OverSampling 	= UART_OVERSAMPLING_16;

	HAL_UART_Init(&UART_InitStruct);

  /* USART2 icin kesme biriminin oncul tanimlanmasi */
  HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_UART_Receive_IT(&UART_InitStruct, &ulasan, 1);
	
  while (1)
  {

  }
}

