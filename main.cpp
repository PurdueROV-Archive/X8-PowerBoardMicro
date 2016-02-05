//put all of your #includes into main.h file
#include "main.h"

#include "print.h"

/*CAN2 communication    
    PB12  ------> CAN2_RX
    PB13  ------> CAN2_TX 
    	* I2C_HandleTypeDef hcan2			  */

/*I2C1: Pressure sensor/IMU    
    PB10  ------> I2C1_SDA
    PB11  ------> I2C1_SCL 
    	* CAN_HandleTypeDef hi2c2			  */

/*esc for hydraulics
    PC6  ------> TIM2_CH1 
    	*TIM_OC_InitTypeDef sConfigOC
    	*TIM_HandleTypeDef htim3
    	*TIM_CHANNEL_1						  */

/*USART1 
        PA9     ------> USART1_TX
        PA10    ------> USART1_RX
       		* UART_HandleTypeDef huart1   	*/

/* 	USEFULL FUNCTIONS

	RED; BLUE; GREEN; ORANGE

	void LedOn(int ledNum);
	void LedOff(int ledNum);
	void LedToggle(int ledNum);
*/

/*	
	Example how to send can code 
		
	CanHandle.pTxMsg->DLC = 3; //sets the size of the message in bytes. Max 8 bytes per message

	//sets the information that is sent over the message
	CanHandle.pTxMsg->Data[0] = 5;
    CanHandle.pTxMsg->Data[1] = 246;
    CanHandle.pTxMsg->Data[2] = 17;

	HAL_CAN_Transmit(&hcan2, 10);  //sends the message
*/	

int main(void) {

	initEverythig();

	while (1) {

		LedToggle(ORANGE);
		HAL_Delay(500);
	}
}

/* This function is where messages from CAN
   communication are received */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle)
{
	int check = 1; //for bytes check
		//example on how to use this in callback function
	if ((CanHandle->pRxMsg)->StdId == MAIN_CAN_ID  && (CanHandle->pRxMsg)->IDE == CAN_ID_STD)
	{
		//if the data length is 8
		if ((CanHandle->pRxMsg)->DLC == 8)
		{
			int j;
			switch (receiveState) {
				case 0:
					j = 0;
					for (int i = 0; i < (CanHandle->pRxMsg)->DLC; i++) {
						thruster[j] = (CanHandle->pRxMsg)->Data[i];
						thruster[j] = thruster[j] << 8;
						thruster[j] += (CanHandle->pRxMsg)->Data[++i];
						j++;
					}
					//Test if all thruster commands are one
					for (int i = 0; i < 4; i++)
						if (thruster[i] != 1)
							check = 0;

					if (check == 0)
						LedOn(RED);
					else
						LedOff(RED);
					receiveState++;
					break;
				case 1:
					j = 4;
					for (int i = 0; i < (CanHandle->pRxMsg)->DLC; i++) {
						thruster[j] = (CanHandle->pRxMsg)->Data[i];
						thruster[j] = thruster[j] << 8;
						thruster[j] += (CanHandle->pRxMsg)->Data[++i];
						j++;
					}
					//Test if all thruster commands are one
					for (int i = 4; i < 8; i++)
						if (thruster[i] != 1)
							check = 0;

					if (check == 0)
						LedOn(GREEN);
					else
						LedOff(GREEN);
					receiveState++;
					break;
				//blink the orange light if a message containing all ones is received
			}
		}
		else {
			if ((CanHandle->pRxMsg)->DLC == 1) {
				receiveState = 0;
			}
		}
	}
	//restarts the interrupt
	if(HAL_CAN_Receive_IT(CanHandle, CAN_FIFO0) == HAL_OK)
		LedToggle(BLUE);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {

}



