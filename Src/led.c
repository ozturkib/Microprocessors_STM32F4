#include "main.h"

#define BEKLEME_SURESI_SABIT 		300 //BEKLEME_SURESI=300 -> Beleme suresi 300 milisaniyedir.
#define BEKLEME_SURESI_ARTIS 		50
#define BEKLEME_SURESI_MIN   		50
#define BEKLEME_SURESI_MAX   		500

#define BEKLEME_SURE_1SN				1000

#define ODEV_A	 		 						'A'
#define ODEV_B	 		 						'B'

void LED_Yak_Sondur_Sabit_Aralikli(uint16_t sure){
	/*
		 4 ledin ayni anda yakilip ayni anda sondurulmesi
	*/

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
	HAL_Delay(sure);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_Delay(sure);
}

void LED_Yak_Sondur_Degisken_Aralikli(uint16_t sure_min, uint16_t sure_max, uint16_t sure_artis){
	/*
		4 Ledin 
		ornegin su sekilde calistirilmasi >> 
		50ms, 100ms, 150ms, 200ms, 	...., 500ms, 50ms, 100ms, ...
	*/
	uint16_t sure;
	for(sure = sure_min; sure <= sure_max; sure += sure_artis)
		LED_Yak_Sondur_Sabit_Aralikli(sure);
}


void LED_GPIO_Odev2aApp(void){
	/*
		Odev ayrintilari : http://oku.ozturkibrahim.com/docs/Microprocessors_HW02_GPIO_LED.pdf
		 4 ledin ayni anda yakilip ayni anda sondurulmesi
		 Ve her bir yanis-sonus arasinda BEKLEME_SURESI kadar zaman gecirilir.
	*/
	LED_Yak_Sondur_Sabit_Aralikli(BEKLEME_SURESI_SABIT);			
}

void LED_GPIO_Odev2bApp(void){
	/*
		Odev ayrintilari : http://oku.ozturkibrahim.com/docs/Microprocessors_HW02_GPIO_LED.pdf
		4 Ledin 
		ornegin su sekilde calistirilmasi >> 
		50ms, 100ms, 150ms, 200ms, 	...., 500ms, 50ms, 100ms, ...
	*/
	LED_Yak_Sondur_Degisken_Aralikli(BEKLEME_SURESI_MIN, BEKLEME_SURESI_MAX, BEKLEME_SURESI_ARTIS);
}


void LED_GPIO_Odev2BirlestirmeApp(void){
	/*
		Odev ayrintilari : http://oku.ozturkibrahim.com/docs/Microprocessors_HW02_GPIO_LED.pdf
	*/
	uint8_t odevTipi = ODEV_B;
	if (odevTipi == ODEV_A)			 //Odev-a
	{
		LED_GPIO_Odev2aApp();
	}
	else if (odevTipi == ODEV_B)	//Odev-b
	{
		LED_GPIO_Odev2bApp();
	}
}


void LED_GPIO_RingApp(void)
{
	/**
		Kullanici kullanimi icin ayrilan 4 LED'in 1 saniye sureyle
		Sirasiyla yakilmasi
		LED PD12-LED PD13,LED PD14,LED PD15,LED PD12,...
	**/
	LED_GPIO_Sirayla_Yak();
}

void Sadece_Tek_Ledi_Yak(uint16_t led_pini)
{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);	
		HAL_GPIO_WritePin(GPIOD, led_pini, GPIO_PIN_SET);
		HAL_Delay(BEKLEME_SURE_1SN);
}

void LED_GPIO_Sirayla_Yak(void)
{
		Sadece_Tek_Ledi_Yak(GPIO_PIN_12);
		Sadece_Tek_Ledi_Yak(GPIO_PIN_13);
		Sadece_Tek_Ledi_Yak(GPIO_PIN_14);
		Sadece_Tek_Ledi_Yak(GPIO_PIN_15);
}

void LED_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*GPIO PD12, PD13, PD14 ve PD15 e bagli LED'lerin oncul tanimlamasi*/
  GPIO_InitStruct.Pin 	= GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull 	= GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
