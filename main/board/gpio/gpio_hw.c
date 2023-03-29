/*
 * gpio_hw.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Admin
 */



#include "gpio_hw.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

void gpio_init(MBS_GPIO *gpio){
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    if(gpio->mode == GPIO_OUTPUT){
    	io_conf.mode = GPIO_MODE_OUTPUT;
    }
    else{
    	io_conf.mode = GPIO_MODE_INPUT;
    }
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = (1ULL<<gpio->pin);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}
GPIO_PIN_LEVEL gpio_read(MBS_GPIO *gpio){
	gpio->level = gpio_get_level(gpio->pin);
	return gpio->level;
}
void gpio_pin_write(MBS_GPIO *gpio, GPIO_PIN_LEVEL level){
	gpio->level = level;
	gpio_set_level(gpio->pin,gpio->level);
}
void gpio_pin_toggle(MBS_GPIO *gpio){
	gpio->level == GPIO_PIN_SET ? gpio_pin_write(gpio,GPIO_PIN_RESET):gpio_pin_write(gpio,GPIO_PIN_SET);
}


MBS_GPIO gpio_warning = {.pin = WARNING_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO};
MBS_GPIO gpio_nodeid[8] = {
		{.pin = Node_1_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_2_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_3_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_4_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_5_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_6_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_7_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
		{.pin = Node_8_GPIO,.mode = GPIO_OUTPUT,.pull_en = PULL_UP_NO},
};
MBS_GPIO led_wifi = { .pin = WIFI_LED_PIN, .mode = GPIO_OUTPUT, .pull_en =
		PULL_UP_NO };
MBS_GPIO button_gpio = {.pin = BUTTON_GPIO,.mode = GPIO_INPUT,.pull_en = PULL_UP_EN};
