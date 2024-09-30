#include <stdio.h>
#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <unity.h>
#include "signaling.h"
#include <semphr.h>

#define TEST_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define TEST_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define TEST_RUNNER_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define TEST_RUNNER_STACK_SIZE configMINIMAL_STACK_SIZE


void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data)
{
    // Wait until a semaphore signal asserted
    xSemaphoreTake(request, portMAX_DELAY);

    // Do Calculation
    signal_data->output = signal_data->input + 5;

    // Signal calculation complete
    xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data)
{
    // Wait until a semaphore signal asserted
    xSemaphoreGive(request);

    // Signal calculation complete
    return xSemaphoreTake(response, portMAX_DELAY);
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);

    vTaskStartScheduler();
	return 0;
}