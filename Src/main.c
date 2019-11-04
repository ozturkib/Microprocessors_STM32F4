#include "main.h"

int main(void)
{
  HAL_Init();
  SystemClock_Config();

	LED_GPIO_Init();
	Button_GPIO_Init();
	
  while (1)
	{
		/*
			Asagidaki Application fonksiyonlarindan ayni anda sadece biri aktif olmali.
			Pasif olanlar yorum satiri icerisinde kalmali!
		*/
		//LED_GPIO_Odev2aApp();
		//LED_GPIO_Odev2bApp();			
		//LED_GPIO_Odev2BirlestirmeApp();
		//LED_GPIO_RingApp();
		Button_App();
	}
}






