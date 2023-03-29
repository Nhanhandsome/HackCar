#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <board.h>
#include <modbus/modbus_slave.h>
#include <app_led_init.h>
void app_main(void)
{
	board_init();
	app_led_init();
	app_modbus_init();
    while (true) {
        sleep(1);
    }
}
