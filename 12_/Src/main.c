#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void uart1_init (void);
void uart2_init (void);

uint8_t tx_buffer1[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
uint8_t rx_buffer1[10];

uint8_t tx_buffer2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
uint8_t rx_buffer2[10];

uint32_t  rx_counter1, tx_counter1;
uint32_t  rx_counter2, tx_counter2;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		tx_counter1++;
	}

	if (huart->Instance == USART2) {
		tx_counter2++;
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		rx_counter1++;
	}
	if (huart->Instance == USART2) {
		rx_counter2++;
	}
}

int main (void)
{

	HAL_Init();
	uart1_init();
	uart2_init();

	HAL_UART_Transmit_IT(&huart1, tx_buffer1, 10);
	HAL_UART_Receive_IT(&huart1, rx_buffer1, 10);

	HAL_UART_Transmit_IT(&huart2, tx_buffer2, 10);

	while(1)
	{
		;
		HAL_Delay(10);
	}
}

void uart1_init (void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	__HAL_RCC_USART1_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Configure UART module
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&huart1);

	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void uart2_init (void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Configure UART module
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&huart1);

	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void USART1_IRQHandler (void)
{
	HAL_USART_IRQHandler(&huart1);
}

void USART2_IRQHandler (void)
{
	HAL_USART_IRQHandler(&huart2);
}
