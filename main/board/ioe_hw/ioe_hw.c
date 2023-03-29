/*
 * ioe_hw.c
 *
 *  Created on: Dec 15, 2022
 *      Author: quangnd
 */

#include "ioe_hw.h"
#include "huart.h"

static void f_on(IOExtern_Hw *p_io);
static void f_off(IOExtern_Hw *p_io);
static void f_set_color(IOExtern_Hw *p_io,IOE_Color color);
static void f_blink_en(IOExtern_Hw *p_io);
static void f_blink_dis(IOExtern_Hw *p_io);
static void f_write(IOExtern_Hw *ioe);

void ioe_hw_init(IOExtern_Hw *p_io){
	p_io->data = 0;
	p_io->on = f_on;
	p_io->off = f_off;
	p_io->set_color = f_set_color;
	p_io->blink_en = f_blink_en;
	p_io->blink_disable = f_blink_dis;
	p_io->write = f_write;
}
void ioe_hw_deinit(IOExtern_Hw *p_io){

}

static void f_on(IOExtern_Hw *p_io){

}
static void f_off(IOExtern_Hw *p_io){

}
static void f_set_color(IOExtern_Hw *p_io,IOE_Color color){

}
static void f_blink_en(IOExtern_Hw *p_io){

}
static void f_blink_dis(IOExtern_Hw *p_io){

}
static void f_write(IOExtern_Hw *ioe){
	HAL_UART_Transmit(&huart1,&ioe->data,1);
}

IOExtern_Hw ioe_hw;
