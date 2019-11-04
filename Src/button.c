#include "main.h"

void Button_App(void)
{
	/**
		Buton kullanimi : PA0'a bagli buton degerini okumu
		Istenen islev:
			Eger buton basiliysa PD12 ye bagli LED yansin.
			Eger buton basili degilse PD12 ye bagli LED sonsun.
	**/
	GPIO_PinState butonBasiliMi;
	butonBasiliMi = Button_Read();
	if(butonBasiliMi == GPIO_PIN_RESET)	//basilidegilse >> Push-pull down >> GND >> 0
	{
		//Ledi sondur
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

	}
	else if(butonBasiliMi == GPIO_PIN_SET) //basiliysa >> Push-pull down >> VCC >> 1
	{
		//Ledi yak
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
}

void Button_GPIO_Init(void)
{
	//Buton oncul tanimlama : PA0'a bagli buton pini
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*Butonun bagli oldugu portun clock'unun aktiflestirilmesi*/
  __HAL_RCC_GPIOA_CLK_ENABLE();

	/* PA0'a bagli buton init ayarlari */
  GPIO_InitStruct.Pin 	= GPIO_PIN_0;
  GPIO_InitStruct.Mode 	= GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull 	= GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

GPIO_PinState Button_Read(void)
{
	GPIO_PinState buttonDegeri;
	buttonDegeri = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	return buttonDegeri;
}

