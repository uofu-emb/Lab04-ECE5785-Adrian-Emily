#include <stdio.h>
#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "signaling.h"
#include <semphr.h>


void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data)
{
    // Wait until a semaphore signal asserted
    xSemaphoreTake(request, portMAX_DELAY);

    // Do Calculation
    data->output = data->input + 5;

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
