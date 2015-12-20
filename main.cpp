//put all #includes into main.h
#include "main.h" 

/**TIM3 GPIO Configuration    
    PC6  ------> TIM3_CH1 */

/**CAN2 GPIO Configuration    
    PB12 ------> CAN2_RX
    PB13 ------> CAN2_TX */

/**I2C1 GPIO Configuration    
    PB6  ------> I2C1_SCL
    PB7  ------> I2C1_SDA */


/* 	USEFULL FUNCTIONS
	
	RED = ?; BLUE = ?; GREEN = ?; YELLOW = ?

	void LedOn(int ledNum);
	void LedOff(int ledNum);
	void LedToggle(int ledNum);
*/

int main(void)  
{
	//does all of the initializations for you! 
    initEverythig();

	while (1)
	{
		
    }
}


/* This function is where messages from CAN
   communication are received */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle)
{
	//example on how to use this in callback function
	if ((CanHandle->pRxMsg)->StdId == 0x11 && (CanHandle->pRxMsg)->IDE == CAN_ID_STD)
	{


	}
}




