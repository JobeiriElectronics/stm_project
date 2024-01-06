#define BTN_PORT GPIOC
#define BTN_PIN GPIO_PIN_13

void gpio_pc13_interrupt_init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void EXTI15_10_IRQHandler(void);
