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
	uint8_t test = 0;
	while (1) {
		/* Test Sending Data back to main micro board */
		hcan2.pTxMsg->DLC = 1;
		hcan2.pTxMsg->Data[0] = 7;
		HAL_CAN_Transmit(&hcan2, 100);
		hcan2.pTxMsg->DLC = 8;
		hcan2.pTxMsg->Data[0] = 0xAB;
		hcan2.pTxMsg->Data[1] = 0xAB;
		hcan2.pTxMsg->Data[2] = 0xAB;
		hcan2.pTxMsg->Data[3] = (test > 1 ? 0xAB : 0x88);
		hcan2.pTxMsg->Data[4] = 0xAB;
		hcan2.pTxMsg->Data[5] = 0xAB;
		hcan2.pTxMsg->Data[6] = 0xAB;
		hcan2.pTxMsg->Data[7] = 0xAB;
		HAL_CAN_Transmit(&hcan2, 100);
		test = (test >= 4 ? 0 : test + 1);
		HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);
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
					for(int i = 0; i < 8; i++)
					{
						printInt(i);
						printString(": ");
						printInt(thruster[i]);
						printString("\t");
					}
					printString("\n");

					receiveState++;
					break;
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


