/*
 * ioe_hw.h
 *
 *  Created on: Dec 15, 2022
 *      Author: quangnd
 */

#ifndef MAIN_BOARD_IOE_HW_IOE_HW_H_
#define MAIN_BOARD_IOE_HW_IOE_HW_H_

#include "stdio.h"
#include "stdint.h"

typedef enum{
	IO_RED = 1,
	IO_GREEN,
	IO_BLUE,
}IOE_Color;

typedef struct IOExtern_Hw_t IOExtern_Hw;

typedef void (*ioe_on)(IOExtern_Hw *p_io);
typedef void (*ioe_off)(IOExtern_Hw *p_io);
typedef void (*ioe_set_color)(IOExtern_Hw *p_io,IOE_Color color);
typedef void (*ioe_blink_en)(IOExtern_Hw *p_io);
typedef void (*ioe_blink_disable)(IOExtern_Hw *p_io);
typedef void (*ioe_write)(IOExtern_Hw *ioe);

struct IOExtern_Hw_t{
	uint8_t data;
	ioe_on on;
	ioe_off off;
	ioe_set_color set_color;
	ioe_blink_en blink_en;
	ioe_blink_disable blink_disable;
	ioe_write write;
};

void ioe_hw_init(IOExtern_Hw *p_io);
void ioe_hw_deinit(IOExtern_Hw *p_io);

extern IOExtern_Hw ioe_hw;

#endif /* MAIN_BOARD_IOE_HW_IOE_HW_H_ */
