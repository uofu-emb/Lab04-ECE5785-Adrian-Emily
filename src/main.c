#include <stdio.h>
#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);

    vTaskStartScheduler();
	return 0;
}