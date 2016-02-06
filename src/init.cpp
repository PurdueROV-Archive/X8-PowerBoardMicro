/*This folder will be used to hold all code used to initialize pins */

#include "init.h"
#include "stm32f4xx_hal.h"

uint16_t thruster[8];
uint8_t receiveState = 255;
uint16_t voltage[8];
uint16_t current[8];

TIM_OC_InitTypeDef sConfigOC;

CAN_HandleTypeDef hcan2;

CanTxMsgTypeDef        TxMessage;
CanRxMsgTypeDef        RxMessage;

I2C_HandleTypeDef hi2c2;

DMA_HandleTypeDef hdma_i2c2_rx;
DMA_HandleTypeDef hdma_i2c2_tx;


TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;


//this function will call all of the other initialization functions
void initEverythig(void)
{
	/* GPIO Ports Clock Enable */
 	__GPIOA_CLK_ENABLE();
 	__GPIOB_CLK_ENABLE();
 	__GPIOC_CLK_ENABLE();
 	__GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();


 	//must be included to initially configure the library
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	initDebugLeds();

	HAL_MspInit();

	MX_DMA_Init();


	CAN_init();

	

	MX_I2C2_Init();
	MX_USART1_UART_Init();


	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	initPwm();
}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart1);

}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if(huart->Instance==USART1)
	{
				__USART1_CLK_ENABLE();

		/**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* Peripheral DMA init*/

		hdma_usart1_rx.Instance = DMA2_Stream2;
		hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
		hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_rx.Init.Mode = DMA_NORMAL;
		hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_usart1_rx);

		__HAL_LINKDMA(huart,hdmarx,hdma_usart1_rx);

		hdma_usart1_tx.Instance = DMA2_Stream7;
		hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_tx.Init.Mode = DMA_NORMAL;
		hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_usart1_tx);

		__HAL_LINKDMA(huart,hdmatx,hdma_usart1_tx);

		/* Peripheral interrupt init*/
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);

	}

}

/* checked! */
void initPwm(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__TIM3_CLK_ENABLE();

	/**TIM3 GPIO Configuration
    PC6     ------> TIM3_CH1
    */
	GPIO_InitStruct.Pin = esc_pwm_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(esc_pwm_GPIO_Port, &GPIO_InitStruct);


	//TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = SystemCoreClock;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 1000;
	htim3.Init.ClockDivision = 0;
	HAL_TIM_PWM_Init(&htim3);

	/*sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);*/

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 500;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

}

/* Not used initialization for I2C */
/*void initI2C(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;



    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);





    __I2C1_CLK_ENABLE();

    hdma_i2c1_rx.Instance = DMA1_Stream0;
    hdma_i2c1_rx.Init.Channel = DMA_CHANNEL_1;
    hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_rx.Init.Mode = DMA_NORMAL;
    hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_i2c1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_i2c1_rx);

    __HAL_LINKDMA(&hi2c1,hdmarx,hdma_i2c1_rx);

    hdma_i2c1_tx.Instance = DMA1_Stream6;
    hdma_i2c1_tx.Init.Channel = DMA_CHANNEL_1;
    hdma_i2c1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_i2c1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.Mode = DMA_NORMAL;
    hdma_i2c1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_i2c1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_i2c1_tx);

    __HAL_LINKDMA(&hi2c1,hdmatx,hdma_i2c1_tx);

    hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
 	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  	hi2c1.Init.OwnAddress1 = 0;
  	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  	hi2c1.Init.OwnAddress2 = 0;
  	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  	HAL_I2C_Init(&hi2c1);
}*/

/* I2C1 init function */
void MX_I2C2_Init(void)
{

	hi2c2.Instance = I2C2;
	hi2c2.Init.ClockSpeed = 100000;
	hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	HAL_I2C_Init(&hi2c2);

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if(hi2c->Instance==I2C2)
	{


		/**I2C2 GPIO Configuration
        PB10     ------> I2C2_SCL
        PB11     ------> I2C2_SDA
        */
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		// Peripheral clock enable
				__I2C2_CLK_ENABLE();

		// Peripheral DMA init

		hdma_i2c2_rx.Instance = DMA1_Stream2;
		hdma_i2c2_rx.Init.Channel = DMA_CHANNEL_7;
		hdma_i2c2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_i2c2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_i2c2_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_i2c2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_i2c2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_i2c2_rx.Init.Mode = DMA_NORMAL;
		hdma_i2c2_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_i2c2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_i2c2_rx);

		__HAL_LINKDMA(hi2c,hdmarx,hdma_i2c2_rx);

		hdma_i2c2_tx.Instance = DMA1_Stream7;
		hdma_i2c2_tx.Init.Channel = DMA_CHANNEL_7;
		hdma_i2c2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_i2c2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_i2c2_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_i2c2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_i2c2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_i2c2_tx.Init.Mode = DMA_NORMAL;
		hdma_i2c2_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_i2c2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_i2c2_tx);

		__HAL_LINKDMA(hi2c,hdmatx,hdma_i2c2_tx);


	}

}

void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);

	//USART DMA initialization
			__DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);


}

//sets up the pins for can to be alternate functions
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if(hcan->Instance==CAN2)
	{

		/* Peripheral clock enable */
		__CAN2_CLK_ENABLE();
		__CAN1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();

		/**CAN1 GPIO Configuration
        PB12     ------> CAN1_RX
        PB13     ------> CAN1_TX
        */
		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral interrupt init*/
		HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
		HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
	}

}

HAL_StatusTypeDef CAN_init(void)
{

	CAN_FilterConfTypeDef  sFilterConfig;


	/*##-1- Configure the CAN peripheral #######################################*/
	hcan2.Instance = CAN2;
	hcan2.pTxMsg = &TxMessage;
	hcan2.pRxMsg = &RxMessage;


	//standard settings for can bus
	hcan2.Init.TTCM = DISABLE;
	hcan2.Init.ABOM = DISABLE;
	hcan2.Init.AWUM = DISABLE;
	hcan2.Init.NART = DISABLE;
	hcan2.Init.RFLM = DISABLE;
	hcan2.Init.TXFP = DISABLE;
	hcan2.Init.Mode = CAN_MODE_NORMAL;
	hcan2.Init.SJW = CAN_SJW_1TQ;
	hcan2.Init.BS1 = CAN_BS1_6TQ;
	hcan2.Init.BS2 = CAN_BS2_8TQ;
	hcan2.Init.Prescaler = 2;

	//if can is unable to initialize
	if(HAL_CAN_Init(&hcan2) != HAL_OK)
	{

	}

	/*##-2- Configure the CAN Filter ###########################################*/
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 0;

	if(HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK)
	{

	}

	//sets up the communication information
	hcan2.pTxMsg->StdId = CAN_ID;  //the id of this microboard


	hcan2.pTxMsg->RTR = CAN_RTR_DATA;
	hcan2.pTxMsg->IDE = CAN_ID_STD;


	HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);

	return HAL_OK; /* Test Passed */
}



void HAL_MspInit(void)
{
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

//initialize the debugging leds
void initDebugLeds(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	//enable the led clock
	 __HAL_RCC_GPIOD_CLK_ENABLE();

	//configures the led pin  
	GPIO_InitStruct.Pin = GPIO_PIN_12; 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);  

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); 

	GPIO_InitStruct.Pin = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); 

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); 

}

//turns on and turns off the led
void LedOn(int ledNum)
{
	if(ledNum == 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else if(ledNum == 1)
	{	
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else if(ledNum == 2)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	}
	else if(ledNum == 3)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	}
}

//turns on and turns off the led
void LedOff(int ledNum)
{
	if(ledNum == 0)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	}
	else if(ledNum == 1)
	{	
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	}
	else if(ledNum == 2)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	}
	else if(ledNum == 3)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	}
}

//turns on and turns off the led
void LedToggle(int ledNum)
{
	if(ledNum == 0)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	}
	else if(ledNum == 1)
	{	
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	}
	else if(ledNum == 2)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	}
	else if(ledNum == 3)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
	}
}

//configures the system clcok
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;

			__PWR_CLK_ENABLE();

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

//function used to handle errors
void Error_Handler(void)
{
  while(1)
  {
  }
}
