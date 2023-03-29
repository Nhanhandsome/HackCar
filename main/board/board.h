/*
 * board.h
 *
 *  Created on: Dec 14, 2022
 *      Author: MinhNhan
 */

#ifndef MAIN_BOARD_BOARD_H_
#define MAIN_BOARD_BOARD_H_

#include "drv_timer.h"
#include "hw_flash.h"
#include "can_hw/can_hw.h"
#include "uart_hw/huart.h"
#include "gpio/gpio_hw.h"
#include "ioe_hw/ioe_hw.h"

void board_init(void);
void board_deinit(void);

extern char auther_str[50];

#endif /* MAIN_BOARD_BOARD_H_ */
