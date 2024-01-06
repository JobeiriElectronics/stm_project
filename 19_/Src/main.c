#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"

#define BUFFER_SIZE 32
#define DMA_STREAM DMA2_Stream0
#define DMA_STREAM_IRQ DMA2_Stream0_IRQn
#define DMA_STREAM_IRQHANDLER DMA2_Stream0_IRQHandler
#define DMA_CHANNEL DMA_CHANNEL_0

DMA_HandleTypeDef DmaHandle;

static void dma_config (void);
static void TransferComplete(DMA_HandleTypeDef *DmaHandle);
static void TransferError(DMA_HandleTypeDef *DmaHandle);

static const uint32_t aSRC_Const_Buffer [BUFFER_SIZE] = {
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030,
		0x10101010, 0x02020202, 0x20202020, 0x30303030
};

static const uint32_t aDST_Buffer [BUFFER_SIZE];

int main (void)
{

	HAL_Init();
	uart_init();

	dma_config();


	while(1)
	{

	}
}

static void dma_config (void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

	DmaHandle.Instance = DMA_STREAM;
	DmaHandle.Init.Channel = DMA_CHANNEL;
	DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;
	DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;
	DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
	DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;
	DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
	DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
	DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;

	HAL_DMA_Init(&DmaHandle);

	HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
	HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, TransferError);

	HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);

	HAL_DMA_Start_IT(&DmaHandle, (uint32_t) &aSRC_Const_Buffer, (uint32_t) &aDST_Buffer, BUFFER_SIZE);
}

static void TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
	// do something
	printf("Transfer Complete \n\r");
}

static void TransferError(DMA_HandleTypeDef *DmaHandle)
{
	// do something
	printf("Transfer Error \n\r");
}

void DMA_STREAM_IRQHANDLER (void)
{
	HAL_DMA_IRQHandler(&DmaHandle);
}

void SysTick_Handler (void)
{
	HAL_IncTick();
}
