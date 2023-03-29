/*
 * board.c
 *
 *  Created on: Dec 14, 2022
 *      Author: MinhNhan
 */

#include "board.h"
#include "esp_random.h"
#include "stdio.h"

char auther_str[50] = {0};

void board_init(void){
	flash_init();
	can_hardware_init();
	drv_timer_init();
	HAL_UART_Init(&huart1);

	gpio_init(&gpio_nodeid[1]);
	gpio_pin_write(&gpio_nodeid[1], GPIO_PIN_SET);
	int size = flash_read_str("auther", auther_str);
	if(size == -1){
		uint32_t auther = esp_random();
		printf("Auther : 0x%08X\n",(unsigned int)auther);
		sprintf(auther_str,"%08X",(unsigned int)auther);
		flash_write_str("auther",auther_str);
	}
}
void board_deinit(void){
	can_hardware_deinit();
}


