#include "stm32f4xx_hal.h"

#define BTN_PORT  GPIOC
#define BTN_PIN   GPIO_PIN_13
#define LED_PORT  GPIOA
#define LED_PIN   GPIO_PIN_5

//BTN = PC13, BUS = AHB1EN bit0
//LED = PA5,  BUS = AHB1EN bit2

// function declaration
void pa5_led_init(void);
void pc13_btn_init(void);

uint8_t buttonStatus;

int main()
{
	// HAL_Init();
	pa5_led_init();
	pc13_btn_init();

	while(1)
	{
		 // buttonStatus is 1 when i
		 buttonStatus = HAL_GPIO_ReadPin (BTN_PORT, BTN_PIN);
		 HAL_GPIO_WritePin(LED_PORT, LED_PIN, buttonStatus);
	}
}

// function definition
void pa5_led_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	 GPIO_InitStruct.Pin   =  LED_PIN;
	 GPIO_InitStruct.Mode  =  GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Pull  =  GPIO_NOPULL;
	 GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);
}
void pc13_btn_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin   =  BTN_PIN;
	GPIO_InitStruct.Mode  =  GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  =  GPIO_NOPULL;
	GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);
}
void SysTick_Handler(void)
{
	HAL_IncTick();
}

