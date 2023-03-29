/*
 * drv_timer.c
 *
 *  Created on: Aug 21, 2022
 *      Author: Giangnv
 */

#include "drv_timer.h"

#include <stdint.h>


#define TIMER_INTERVAL			1000 /*1ms*/

#define TIMER_SEC				1000000 /*1ms*/

#define NUM_TIMERS_CB		(4)

static void Timer_msec_handler(void* arg);

static void Timer_sec_handler(void* arg);

typedef void (*pfnTimer)(void);

pfnTimer pfnTimer_sec[NUM_TIMERS_CB];
pfnTimer pfnTimer_msec[NUM_TIMERS_CB];

int cnt_ms = 0;

uint32_t sec_ticks = 0;
uint32_t msec_ticks = 0;

esp_timer_handle_t oneshot_timer;

void drv_timer_init(void)
{

    const esp_timer_create_args_t periodic_timer_args = {
            .callback = &Timer_msec_handler,
            /* name is optional, but may help identify the timer when debugging */
            .name = "periodic"
    };

	const esp_timer_create_args_t periodic_timer_sec_args = {
			.callback = &Timer_sec_handler,
			/* name is optional, but may help identify the timer when debugging */
			.name = "periodic_sec"
	};

    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));

    /* The timer has been created but is not running yet */
    //timer sec
	esp_timer_handle_t periodic_sec_timer;
	ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_sec_args, &periodic_sec_timer));

    /* Start the timers */
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, TIMER_INTERVAL));

    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_sec_timer, TIMER_SEC));

//    /* Clean up and finish the example */
//    ESP_ERROR_CHECK(esp_timer_stop(periodic_timer));
//    ESP_ERROR_CHECK(esp_timer_delete(periodic_timer));
}




void drv_timer_register_callback(void timer_cb(void), type_timer_t timer)
{
	if(timer_cb == NULL)
		return;

	if(timer == timer_sec)
	{
		for(uint8_t ui = 0; ui < NUM_TIMERS_CB; ui ++)
		{
			if(pfnTimer_sec[ui] == NULL)
			{
				pfnTimer_sec[ui] = timer_cb;
				return;
			}
		}
	}
	else if(timer == timer_msec)
	{
		for(uint8_t ui = 0; ui < NUM_TIMERS_CB; ui ++)
		{
			if(pfnTimer_msec[ui] == NULL)
			{
				pfnTimer_msec[ui] = timer_cb;
				return ;
			}
		}
	}

	return;
}

void drv_timer_unregister_callback(void timer_cb(void), type_timer_t timer)
{
	if(timer_cb == NULL)
		return;

	if(timer == timer_sec)
	{
		for(uint8_t ui = 0; ui < NUM_TIMERS_CB; ui ++)
		{
			if(pfnTimer_sec[ui] == timer_cb)
			{
				pfnTimer_sec[ui] = NULL;
				return;
			}
		}
	}
	else if(timer == timer_msec)
	{
		for(uint8_t ui = 0; ui < NUM_TIMERS_CB; ui ++)
		{
			if(pfnTimer_msec[ui] == timer_cb)
			{
				pfnTimer_msec[ui] = NULL;
				return ;
			}
		}
	}

	return;
}

static void IRAM_ATTR  Timer_msec_handler(void* arg)
{
	msec_ticks ++;
	for(uint8_t ui = 0; ui < NUM_TIMERS_CB; ui ++)
	{
		if(pfnTimer_msec[ui] != NULL)
			pfnTimer_msec[ui]();
	}
}

static void IRAM_ATTR Timer_sec_handler(void* arg)
{
	sec_ticks ++;
	for(uint8_t ui = 0; ui < NUM_TIMERS_CB; ui ++)
	{
		if(pfnTimer_sec[ui] != NULL)
			pfnTimer_sec[ui]();
	}
}

uint32_t drv_timer_get_ticks(void)
{
	return msec_ticks;
}




