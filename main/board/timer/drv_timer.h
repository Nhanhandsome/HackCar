/*
 * drv_timer.h
 *
 *  Created on: Aug 21, 2022
 *      Author: Giangnv
 */

#ifndef DRIVERS_TIMER_DRV_TIMER_H_
#define DRIVERS_TIMER_DRV_TIMER_H_
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_sleep.h"


typedef enum
{
	timer_sec = 0x00,
	timer_msec
}type_timer_t;

void drv_timer_init(void);

void drv_timer_register_callback(void timer_cb(void), type_timer_t timer);

void drv_timer_unregister_callback(void timer_cb(void), type_timer_t timer);

uint32_t drv_timer_get_ticks(void);





#endif /* DRIVERS_TIMER_DRV_TIMER_H_ */
