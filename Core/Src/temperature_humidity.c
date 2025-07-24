#include "temperature_humidity.h"


extern TIM_HandleTypeDef htim1;


uint8_t DHT11_Read(volatile float* temperature,volatile float* humidity)
{
    uint8_t data[5] = {0};

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_Delay(18);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

    for (volatile int i = 0; i < 50; i++);


    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    uint32_t timeout = 0xFFFF;
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET) {
        if (--timeout == 0) return 0;
    }

    timeout = 0xFFFF;
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) {
        if (--timeout == 0) return 0;
    }

    timeout = 0xFFFF;
    while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET) {
        if (--timeout == 0) return 0;
    }


    for (uint8_t byte = 0; byte < 5; byte++) {
        for (int bit = 0; bit < 8; bit++) {

            timeout = 0xFFFF;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) {
                if (--timeout == 0) return 0;
            }

            uint32_t start = __HAL_TIM_GET_COUNTER(&htim1);
            timeout = 0xFFFF;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET) {
                if (--timeout == 0) return 0;
            }
            uint32_t duration = __HAL_TIM_GET_COUNTER(&htim1) - start;


            data[byte] <<= 1;
            if (duration > 40)
                data[byte] |= 1;
            else
                data[byte] |= 0;
        }
    }

    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum != data[4]) return 0;

    *humidity = data[0] + data[1] / 100.0f;
    *temperature = data[2] + data[3] / 100.0f;

    return 1;
}










