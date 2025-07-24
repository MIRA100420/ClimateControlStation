#ifndef __SET_MODE
#define __SET_MODE

#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include "lcd.h"
#include "temperature_humidity.h"

#define set() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)
#define up() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define down() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)

typedef enum{
	BASE,
	SELECT_SET,
	SET_TEMP,
	SET_HUM
} State_t;

extern  State_t state;

extern volatile float set_T;
extern volatile float set_H;
extern bool pointer;



void Work(float,float);

#endif
