#include <stdint.h>

#define SRAM_START 0x20000000u
#define SRAM_SIZE (16 * 1024) //16Kb
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void __libc_init_array(void);

void Reset_Handler(void);

void NMI_Handler                                    (void) __attribute__((weak,alias("Default_Handler")));
void HardFault_Handler                              (void) __attribute__((weak,alias("Default_Handler")));
void SVCall_Handler                                 (void) __attribute__((weak,alias("Default_Handler")));
void PendSV_Handler                                 (void) __attribute__((weak,alias("Default_Handler")));
void SysTick_Handler                                (void) __attribute__((weak,alias("Default_Handler")));
void WWDG_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void RTC_IRQHandler                                 (void) __attribute__((weak,alias("Default_Handler")));
void Flash_IRQHandler                               (void) __attribute__((weak,alias("Default_Handler")));
void RCC_IRQHandler                                 (void) __attribute__((weak,alias("Default_Handler")));
void EXTI0_1_IRQHandler                             (void) __attribute__((weak,alias("Default_Handler")));
void EXTI2_3_IRQHandler                             (void) __attribute__((weak,alias("Default_Handler")));
void EXTI4_15_IRQHandler                            (void) __attribute__((weak,alias("Default_Handler")));
void DMA_CH1_IRQHandler                             (void) __attribute__((weak,alias("Default_Handler")));
void DMA_CH2_3_IRQHandler                           (void) __attribute__((weak,alias("Default_Handler")));
void DMA_CH4_5_IRQHandler                           (void) __attribute__((weak,alias("Default_Handler")));
void ADC_IRQHandler                                 (void) __attribute__((weak,alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler                 (void) __attribute__((weak,alias("Default_Handler")));
void TIM1_CC_IRQHandler                             (void) __attribute__((weak,alias("Default_Handler")));
void TIM3_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void TIM6_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void TIM7_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void TIM14_IRQHandler                               (void) __attribute__((weak,alias("Default_Handler")));
void TIM15_IRQHandler                               (void) __attribute__((weak,alias("Default_Handler")));
void TIM16_IRQHandler                               (void) __attribute__((weak,alias("Default_Handler")));
void TIM17_IRQHandler                               (void) __attribute__((weak,alias("Default_Handler")));
void I2C1_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void I2C2_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void SPI1_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void SPI2_IRQHandler                                (void) __attribute__((weak,alias("Default_Handler")));
void USART1_IRQHandler                              (void) __attribute__((weak,alias("Default_Handler")));
void USART2_IRQHandler                              (void) __attribute__((weak,alias("Default_Handler")));
void USART3_4_5_6_IRQHandler                        (void) __attribute__((weak,alias("Default_Handler")));
void USB_IRQHandler                                 (void) __attribute__((weak,alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)SVCall_Handler,
    0,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_IRQHandler,
    0,
    (uint32_t)RTC_IRQHandler,
    (uint32_t)Flash_IRQHandler,
    (uint32_t)RCC_IRQHandler,
    (uint32_t)EXTI0_1_IRQHandler,
    (uint32_t)EXTI2_3_IRQHandler,
    (uint32_t)EXTI4_15_IRQHandler,
    0,
    (uint32_t)DMA_CH1_IRQHandler,
    (uint32_t)DMA_CH2_3_IRQHandler,
    (uint32_t)DMA_CH4_5_IRQHandler,
    (uint32_t)ADC_IRQHandler,
    (uint32_t)TIM1_BRK_UP_TRG_COM_IRQHandler,
    (uint32_t)TIM1_CC_IRQHandler,
    0,
    (uint32_t)TIM3_IRQHandler,
    (uint32_t)TIM6_IRQHandler,
    (uint32_t)TIM7_IRQHandler,
    (uint32_t)TIM14_IRQHandler,
    (uint32_t)TIM15_IRQHandler,
    (uint32_t)TIM16_IRQHandler,
    (uint32_t)TIM17_IRQHandler,
    (uint32_t)I2C1_IRQHandler,
    (uint32_t)I2C2_IRQHandler,
    (uint32_t)SPI1_IRQHandler,
    (uint32_t)SPI2_IRQHandler,
    (uint32_t)USART1_IRQHandler,
    (uint32_t)USART2_IRQHandler,
    (uint32_t)USART3_4_5_6_IRQHandler,
    0,
    (uint32_t)USB_IRQHandler
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    //Copy .data section to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

    uint8_t *pDst = (uint8_t *)&_sdata; //sram
    uint8_t *pSrc = (uint8_t *)&_la_data; //flash

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    //Initialize .bss section to zero
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t *)&_sbss;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }

    //Call library function
    __libc_init_array();

    //call main()
    main();
}