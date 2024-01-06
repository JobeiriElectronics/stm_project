#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include "tim.h"

// universal asynchronous receiver transmitter

ADC_HandleTypeDef hadc1;

uint32_t sensor_value[1];

int main (void)
{

	HAL_Init();
	uart_init();
	adc_pa0_dma_init ();

	// 1. Start ADC using Interrupts
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *) sensor_value, 1);

	while(1)
	{

	}
}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//	sensor_value = pa0_adc_read();
//}

void SysTick_Handler (void)
{
	HAL_IncTick();
}
