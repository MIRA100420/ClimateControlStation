#include "lcd.h"
#include "string.h"

void LCD_init(){
	HAL_Delay(40);
	rs0();
	LCD_WriteData(30);
	e1();
	delay();
	e0();
	HAL_Delay(40);
	LCD_WriteData(30);
	e1();
	delay();
	e0();
	HAL_Delay(40);
	LCD_WriteData(30);
	e1();
	delay();
	e0();
	HAL_Delay(40);
	LCD_WriteData(0x02); // команда режим 4 бит
	e1();
	delay();
	e0();
	HAL_Delay(40);
	LCD_Command(0x28); // команда режим 4 бит,
	HAL_Delay(1);
	LCD_Command(0x08); // команда выключить дисплей
	HAL_Delay(1);
	LCD_Command(0x01); // команда очистить дисплей
	HAL_Delay(2);
	LCD_Command(0x0F); // команда включить дисплей, включить курсор
	HAL_Delay(1);
}

void LCD_WriteData(uint8_t dt){
	if(dt>>3&0x01){set_b6();}else{reset_b6();}
	if(dt>>2&0x01){set_b5();}else{reset_b5();}
	if(dt>>1&0x01){set_b4();}else{reset_b4();}
	if(dt&0x01){set_b3();}else{reset_b3();}
}

void LCD_Data(uint8_t dt){
	rs1();
	LCD_WriteData(dt>>4);
	e1();
	delay();
	e0();

	LCD_WriteData(dt & 0x0F);
	e1();
	delay();
	e0();
}

void LCD_Command(uint8_t dt){
	rs0();
	LCD_WriteData(dt>>4);
	e1();
	delay();
	e0();

	LCD_WriteData(dt & 0x0F);
	e1();
	delay();
	e0();
}

void LCD_Clear(void){
	LCD_Command(0x01);
	HAL_Delay(2);

}

void LCD_SendChar(char ch){
	LCD_Data((uint8_t) ch);
    delay();

}

void LCD_SendSTR(char* str){
	for(uint8_t i = 0;i < strlen(str) ;i++){
		LCD_SendChar(str[i]);
	}
}



/*void delay(void){
	for(uint16_t i = 0;i<1000;i++){
	}
}*/
