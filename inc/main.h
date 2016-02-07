#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include <stm32f407xx.h>
#include "init.h"
#include "thrust_mapper.h"
#include "overseer.h"


#define esc_pwm_Pin GPIO_PIN_6
#define esc_pwm_GPIO_Port GPIOC

#define CAN_ID	0x11
#define APP_CAN_ID 	0x12
#define MAIN_CAN_ID 0x13

#define GREEN 0
#define ORANGE 1
#define RED 2
#define BLUE 3

//uint16_t thruster[8];

#endif /* __MAIN_H */
