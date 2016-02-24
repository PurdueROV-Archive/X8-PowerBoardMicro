//put all of your #includes into main.h file
#include "main.h"

#include "print.h"

#include "thrust_mapper.h"
#include "overseer.h"


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

// Globals:
Overseer overseer;					// Handles all aspects of thrusters/movement
volatile uint_fast8_t RampTicker;	// Ticker/Timing count for ramping thruster power

int main(void) {

	initEverythig();
	uint8_t test = 0;

	// Create Thruster/Movement Overseer
	overseer = Overseer();

	while (1) {
		/* Test Sending Data back to main micro board */
		/*hcan2.pTxMsg->DLC = 1;
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
		HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);*/
		LedToggle(ORANGE);

		// Checks if new data has come in from Control via UDP.
		overseer.checkForUpdate();

		// If timer is reached, motor power is ramped.
		if (RampTicker >= 20)
        {
            overseer.doRamping();
            RampTicker = 0;
        }

		for(int i = 0; i < 8; i++)
		{
			//PRINT THE DATA HERE
			printString("\nThrusters:\n");
			printString("0: ");
			printInt(thruster[0]);
			printString("\t1: ");
			printInt(thruster[1]);
			printString("\t2: ");
			printInt(thruster[2]);
			printString("\n3: ");
			printInt(thruster[3]);
			printString("\t4: ");
			printInt(thruster[4]);
			printString("\t5: ");
			printInt(thruster[5]);

			//printInt();
			//printString();
		}


		HAL_Delay(200);
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
			int j = 0;

			//checks the first state to see if it is a L or a R
			switch ((CanHandle->pRxMsg)->Data[0]) {

				case 'L':
					for (int i = 1; i < (CanHandle->pRxMsg)->DLC - 1; i++) {
						thruster[j] = (CanHandle->pRxMsg)->Data[i];
						thruster[j] = thruster[j] << 8;
						thruster[j] += (CanHandle->pRxMsg)->Data[++i];
						j++;
					}
					LedToggle(GREEN);
					break;

				case 'R':
					int j = 3;
					for (int i = 1; i < (CanHandle->pRxMsg)->DLC - 1; i++) {
						thruster[j] = (CanHandle->pRxMsg)->Data[i];
						thruster[j] = thruster[j] << 8;
						thruster[j] += (CanHandle->pRxMsg)->Data[++i];
						j++;
					}
					char enabled = 255;
					// TODO: Adjust what are now 0's to their proper values. 
					//	enabled and pivot position also needs to be added to the packets sent.
					overseer.update(vect6Make(thruster[0],thruster[1],thruster[2],thruster[3],thruster[4],thruster[5]), vect3Make(0,0,0), enabled);
					LedToggle(RED);
					break;
			}
		}
		else {
			//handle the error case
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


