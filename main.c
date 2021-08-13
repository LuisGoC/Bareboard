
#include "GPIO.h"
#include "RCC.h"
#define LED_PIN      5

int main ( void )
{

    /* Enable clock for GPIO port A, RCC_AHBENR bit  */
    RCC_GPIOA_CLOCK_ON();

    /* Configure GPIOA pin 5 as output */
    gpioConfig_t gpioHandle;
    gpioHandle.Mode = GPIO_MODE_OUTPUT;
    gpioHandle.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10;
    gpioHandle.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOA_START, &gpioHandle);
    
    for(;;)
    {
        /* Toggle pin 5 from port A */
        gpio_togglePins(GPIOA_START, GPIO_PIN_5);

        /* simple and practical delay */
        _delay(100000);
    }
}
