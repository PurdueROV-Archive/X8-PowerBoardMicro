//put all of your #includes into main.h file
#include "main.h" 

/*CAN2 GPIO Configuration    
    PB5  ------> CAN2_RX
    PB6  ------> CAN2_TX */

/*I2C1 GPIO Configuration    
    PB7  ------> I2C1_SDA
    PB8  ------> I2C1_SCL */

/*TIM2 GPIO Configuration    
    PA5  ------> TIM2_CH1 */

/**TIM5 GPIO Configuration    
    PA0  ------> TIM5_CH1
    PA3  ------> TIM5_CH4 */

/* 	USEFULL FUNCTIONS

	RED = ?; BLUE = ?; GREEN = ?; YELLOW = ?

	void LedOn(int ledNum);
	void LedOff(int ledNum);
	void LedToggle(int ledNum);
*/

int main(void) {
	initEverythig();

	uint8_t aTxBuffer[1] = {1};

	while (1) {


		if(HAL_I2C_Master_Transmit_DMA(&hi2c1, (uint16_t)2, (uint8_t*)aTxBuffer, 1) != HAL_OK)
		{
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_11);
		}


		HAL_Delay(400);

	}
}
/* This function is where messages from CAN
   communication are received */
/*void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle)
{
	//example on how to use this in callback function
	if ((CanHandle->pRxMsg)->StdId == 0x11 && (CanHandle->pRxMsg)->IDE == CAN_ID_STD)
	{


	}
}*/



