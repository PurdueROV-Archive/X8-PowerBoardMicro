#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include <stm32f407xx.h>
#include "init.h"


#define esc_pwm_Pin GPIO_PIN_6
#define esc_pwm_GPIO_Port GPIOC

#define CAN_ID	0x11
#define APP_CAN_ID 	0x12
#define MAIN_CAN_ID 0x13

#endif /* __MAIN_H */
