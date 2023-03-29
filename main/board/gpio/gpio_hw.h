/*
 * gpio_hw.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Admin
 */

#ifndef MAIN_BOARD_GPIO_GPIO_HW_H_
#define MAIN_BOARD_GPIO_GPIO_HW_H_

#include "driver/gpio.h"

#define Node_1_GPIO 23
#define Node_2_GPIO 19
#define Node_3_GPIO 18
#define Node_4_GPIO 5
#define Node_5_GPIO 33
#define Node_6_GPIO 25
#define Node_7_GPIO 26
#define Node_8_GPIO 27
#define WARNING_GPIO 4
#define WIFI_LED_PIN 32
#define BUTTON_GPIO 0
typedef enum{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET
}GPIO_PIN_LEVEL;

typedef enum{
	GPIO_OUTPUT = 0,
	GPIO_INPUT,
}GPIO_MODE_t;

typedef enum{
	PULL_UP_NO = 0,
	PULL_UP_EN,
	PULL_DOWN_EN
}GPIO_Pull_Up_Down_En_t;

typedef struct GPIO_t MBS_GPIO;

struct GPIO_t{
	int pin;
	GPIO_MODE_t mode;
	GPIO_Pull_Up_Down_En_t pull_en;
	GPIO_PIN_LEVEL level;
};

void gpio_init(MBS_GPIO *gpio);
GPIO_PIN_LEVEL gpio_read(MBS_GPIO *gpio);
void gpio_pin_write(MBS_GPIO *gpio, GPIO_PIN_LEVEL level);
void gpio_pin_toggle(MBS_GPIO *gpio);

extern MBS_GPIO gpio_warning;
extern MBS_GPIO gpio_nodeid[8];
extern MBS_GPIO led_wifi;
extern MBS_GPIO button_gpio;

#endif /* MAIN_BOARD_GPIO_GPIO_HW_H_ */
