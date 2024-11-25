
/*-------------FreeRTOS Includes--------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/*-------------Custom Driver Includes--------------*/
#include "gpio.h"
#include "uart.h"

const uint8_t led_one_pin = 5;
const uint8_t led_two_pin = 0;

void GPIO_Config();
void USART2_Config();
void BlinkLedOneTask(void *params);
void BlinkLedTwoTask(void *params);

int main(void)
{
    char buffer[] = "Hello, From UART!\n";
    UART2_GPIO_Init();

    GPIO_Config();
    USART2_Config();
    UART_SendBuffer(USART2, (uint8_t *)buffer, sizeof(buffer));

    if (xTaskCreate(BlinkLedOneTask,
                    "BlinkLedOneTask",
                    (configMINIMAL_STACK_SIZE), // Double the minimal stack size
                    NULL,
                    configMAX_PRIORITIES - 1U,
                    NULL) != pdPASS)
    {
    }

    if (xTaskCreate(BlinkLedTwoTask,
                    "BlinkLedTwoTask",
                    (configMINIMAL_STACK_SIZE), // Double the minimal stack size
                    NULL,
                    configMAX_PRIORITIES - 1U,
                    NULL) != pdPASS)
    {
    }

    vTaskStartScheduler();

    for (;;)
    {
    }

    return 0;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    /* Print or log stack overflow for task debugging */

    for (;;)
        ; // Halt system to debug
}

void GPIO_Config()
{
    GPIO_ClockEnable(GPIOA);

    GPIOConfig_t led_one, led_two;

    led_one.Pin = led_one_pin;
    led_one.Mode = GPIO_MODE_OUTPUT;
    led_one.OType = GPIO_OTYPE_PP;
    GPIO_Init(GPIOA, &led_one);

    led_two.Pin = led_two_pin;
    led_two.Mode = GPIO_MODE_OUTPUT;
    led_two.OType = GPIO_OTYPE_PP;
    GPIO_Init(GPIOA, &led_two);
}

void USART2_Config()
{
    UARTConfig_t uart2;
    uart2.pUARTx = USART2;
    uart2.Init.BaudRate = 115200U;
    uart2.Init.Mode = UART_MODE_TX_ONLY;
    uart2.Init.Parity = UART_PARITY_NONE;
    uart2.Init.Parity = UART_WORD_LEN_8BITS;
    UART_Init(&uart2);
}

void BlinkLedOneTask(void *params)
{
    (void)params; // Unused Task

    for (;;)
    {
        GPIO_WritePin(GPIOA, led_one_pin, GPIO_PIN_LOW);
        vTaskDelay(pdMS_TO_TICKS(1000));

        GPIO_WritePin(GPIOA, led_one_pin, GPIO_PIN_HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void BlinkLedTwoTask(void *params)
{
    (void)params; // Unused Task

    for (;;)
    {
        GPIO_WritePin(GPIOA, led_two_pin, GPIO_PIN_LOW);
        vTaskDelay(pdMS_TO_TICKS(500));

        GPIO_WritePin(GPIOA, led_two_pin, GPIO_PIN_HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
