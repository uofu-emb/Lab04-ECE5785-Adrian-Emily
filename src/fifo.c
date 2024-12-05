#include <stdio.h>
#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "fifo.h"
#include <semphr.h>
#include <queue.h>



void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    while (1)
    {
        // Create a local message buffer
        struct request_msg msg = {};

        // Wait until a message is available
        xQueueReceive(requests, &msg, portMAX_DELAY);

        // Do Calculation
        msg.output = msg.input + 5;

        // Set the worker id
        msg.handled_by = id;

        // Give the processed message back
        xQueueSend(results, (void*) &msg, portMAX_DELAY);
    }
}