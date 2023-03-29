/*
 * huart.h
 *
 *  Created on: Dec 20, 2022
 *      Author: Admin
 */

#ifndef MAIN_BOARD_UART_HW_HUART_H_
#define MAIN_BOARD_UART_HW_HUART_H_

#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"

typedef enum{
	PARITY_NONE = 0,
	PARITY_EVEN,
	PARITY_ODD,
}UART_Parity;

typedef enum{
	DATA_7 = 2,
	DATA_8,
	DATA_9
}UART_Databit;

typedef struct UART_Typedef_t UART_Typedef;

struct UART_Typedef_t{
	uint32_t baurate;
	UART_Parity parity;
	UART_Databit databit;
	int port;
	int pin_tx;
	int pin_rx;
	QueueHandle_t queue;
};
void HAL_UART_Init(UART_Typedef *huart);
int HAL_UART_Transmit(UART_Typedef *huart,uint8_t *data,uint32_t len);
int HAL_UART_Receive(UART_Typedef *huart,uint8_t *data,uint32_t len);
int HAL_UART_Available(UART_Typedef *huart);

extern UART_Typedef huart1;
extern UART_Typedef huart2;
#endif /* MAIN_BOARD_UART_HW_HUART_H_ */
