#include "settings_mode.h"
#include "temperature_humidity.h"
#include "string.h"
#include "stdio.h"


volatile float set_T = 0.0f;
volatile float set_H = 0.0f;
char data_TX[8];
bool pointer = 0;

State_t state = BASE;

void Work(float T, float H){
	switch(state){
		case BASE:
			LCD_Command(0x80);
			LCD_SendSTR("Temperature:");
			LCD_Command(0xC0);
			LCD_SendSTR("Humidity:");

			sprintf(data_TX,"%.1f",T);
			LCD_Command(0x80+12);
			LCD_SendSTR("    ");
			LCD_Command(0x80+12);
			LCD_SendSTR(data_TX);

			sprintf(data_TX,"%.1f",H);
			LCD_Command(0xC0+9);
			LCD_SendSTR("      ");
			LCD_Command(0xC0+9);
			LCD_SendSTR(data_TX);

			if(T > set_T){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
			}else{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
			}

			if(T > set_H){
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
			}else{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
			}
			break;
		case SELECT_SET:
			LCD_Command(0x80+12);
			LCD_SendSTR("    ");
			LCD_Command(0xC0+9);
			LCD_SendSTR("       ");
			if(pointer){
				LCD_Command(0x80+12);
				LCD_SendSTR("*");
				LCD_Command(0xC0+9);
				LCD_SendSTR("      ");
			}else{
				LCD_Command(0x80+12);
				LCD_SendSTR("    ");
				LCD_Command(0xC0+12);
				LCD_SendSTR("*");
			}
			break;
		case SET_TEMP:
			LCD_Clear();
			LCD_Command(0x80);
			LCD_SendSTR("set temp:");
			sprintf(data_TX,"%.1f",set_T);
			LCD_SendSTR(data_TX);
			break;

		case SET_HUM:
			LCD_Clear();
			LCD_Command(0x80);
			LCD_SendSTR("set hum:");
			sprintf(data_TX,"%.1f",set_H);
			LCD_SendSTR(data_TX);
			break;

		default:
			state = BASE;
			break;
	}

}
