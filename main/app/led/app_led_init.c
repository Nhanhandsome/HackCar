/*
 * app_led_init.c
 *
 *  Created on: Mar 29, 2023
 *      Author: MinhNhan
 */


#include "app_led_init.h"
#include "led_strip.h"
#include "stdbool.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"

uint8_t led_display[3][3] = {{0,10,0},{10,0,0},{0,0,10}};

#define BLINK_GPIO 4

TaskHandle_t led_task_handle;

void led_task(void* arg);

led_strip_handle_t led_strip;

led_strip_config_t strip_config = {
    .strip_gpio_num = BLINK_GPIO, // The GPIO that connected to the LED strip's data line
    .max_leds = 1, // The number of LEDs in the strip,
    .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
    .led_model = LED_MODEL_WS2812, // LED strip model
    .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
};

led_strip_rmt_config_t rmt_config = {
    .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
    .resolution_hz = 10 * 1000 * 1000, // 10MHz
    .flags.with_dma = false, // whether to enable the DMA feature
};

void app_led_init(void){
	led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip);
	led_strip_set_pixel(led_strip, 0, 0,255,0);
	led_strip_refresh(led_strip);
	xTaskCreate(led_task,"led task",1024,led_strip,5,&led_task_handle);
}


void led_task(void* arg){
	led_strip_handle_t p_led = (led_strip_handle_t) arg;
	uint16_t i = 0;
	while(1){

		led_strip_set_pixel(p_led, 0,led_display[i][0],led_display[i][1],led_display[i][2]);
		led_strip_refresh(p_led);
		i++;
		if(i>2) i = 0;
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
