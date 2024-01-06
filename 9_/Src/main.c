#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include "tim.h"

// universal asynchronous receiver transmitter

ADC_HandleTypeDef hadc1;

uint32_t sensor_value;

int main (void)
{

	HAL_Init();
	uart_init();
	adc_pa0_single_conv_init ();

	// 1. Start ADC using Interrupts
	HAL_ADC_Start_IT(&hadc1);

	while(1)
	{

	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	sensor_value = pa0_adc_read();
}

void SysTick_Handler (void)
{
	HAL_IncTick();
}
