#define _GPIOx_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define _ADCx_CLK_ENABLE  __HAL_RCC_ADC1_CLK_ENABLE()


uint32_t pa0_adc_read (void);
void adc_init_start (void);
void adc_pa0_single_conv_init (void);
void adc_pa0_interrupt_init(void);
void adc_pa0_dma_init (void);
