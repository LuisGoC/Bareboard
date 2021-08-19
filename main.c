
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"
#define LED_PIN      5

//extern void initialise_monitor_handles(void);
static gpioConfig_t gpioHandle;

int main ( void )
{
    //initialise_monitor_handles();
    //printf("\n");
    /* Enable clock for GPIO port A, RCC_AHBENR bit  */
    RCC_GPIOA_CLOCK_ON();

    /* Configure GPIOA pin 5 as output */
    gpioHandle.Mode = GPIO_MODE_OUTPUT;
    gpioHandle.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10;
    gpioHandle.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOA_START, &gpioHandle);

    gpioHandle.Mode = GPIO_MODE_IT_FALLING;
    gpioHandle.Pin = GPIO_PIN_13;
    gpioHandle.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOC_START, &gpioHandle);

    nvic_SetPriority(EXTI4_15_IRQn, 2);
    nvic_EnableIrq(EXTI4_15_IRQn);
    //printf("%d\n", nvic_GetPendingIrq(RTC_IRQn));
    
    for(;;)
    {
        /* Toggle pin 5 from port A */
        //nvic_SetPendingIrq(RTC_IRQn);

        /* simple and practical delay */
        //_delay(1000000);
    }
}

void EXTI4_15_IRQHandler(void)
{
    gpio_isrHandler(GPIO_PIN_13);
}

void gpio_isrCallback( uint32_t pin )
{
    gpio_togglePins(GPIOA_START, GPIO_PIN_5);   
}