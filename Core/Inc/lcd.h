#ifndef __LCD_H
#define __LCD_H
#include "stm32f1xx_hal.h"

#define set_b3() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)
#define set_b4() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET)
#define set_b5() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET)
#define set_b6() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET)

#define reset_b3() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)
#define reset_b4() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET)
#define reset_b5() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET)
#define reset_b6() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET)

#define rs1() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)
#define rs0() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)
#define e1() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)
#define e0() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)

#define delay() HAL_Delay(1)

void LCD_init(void);

void LCD_Data(uint8_t dt);

void LCD_Clear(void);

void LCD_SendChar(char);

void LCD_SendSTR(char*);

void LCD_WriteData(uint8_t);

void LCD_Command(uint8_t);

#endif
