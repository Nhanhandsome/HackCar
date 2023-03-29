/*
 * can.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */




#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/twai.h"
#include <can_hw.h>
#include "string.h"

#define CAN_TX	27
#define CAN_RX  26

#define TX_GPIO_NUM             CAN_TX
#define RX_GPIO_NUM             CAN_RX
#define NO_OF_MSGS              100
#define EXAMPLE_TAG             "CAN"
#define RX_TASK_PRIO                    0
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
//Filter all other IDs except MSG_ID
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
//Set to NO_ACK mode due to self testing with single module
static const twai_general_config_t g_config = { .mode = TWAI_MODE_NORMAL,
		.tx_io = TX_GPIO_NUM, .rx_io = RX_GPIO_NUM, .clkout_io = TWAI_IO_UNUSED,
		.bus_off_io = TWAI_IO_UNUSED, .tx_queue_len =100, .rx_queue_len = 100,
		.alerts_enabled = TWAI_ALERT_NONE, .clkout_divider = 0 };

static void can_frame_init(twai_message_t* p_frame);
static void can_send_impl(CAN_Hw* p_hw);

static void can_recv_task(void* arg);
TaskHandle_t can_recv_handle;

CAN_Hw can1={
                .baudrate=500UL,
                .receive_handle=NULL,
                .send=can_send_impl,
                .node_id=0,
                .set_baudrate=NULL,
};
#define CAN_DEBUG 0

static void can_recv_task(void* arg){

	CAN_Hw *p_can = (CAN_Hw*)arg;
	for(;;){
//		twai_status_info_t rx_status;
//		twai_get_status_info(&rx_status);
		if (twai_receive(&p_can->rx_msg,2) == ESP_OK){
#if CAN_DEBUG
			ESP_LOG_BUFFER_HEX(EXAMPLE_TAG,p_can->rx_msg.data,
					p_can->rx_msg.data_length_code);
			ESP_LOGI(EXAMPLE_TAG,"ID : 0x%08X",(unsigned int)p_can->rx_msg.identifier);
#endif
				p_can->receive_handle(p_can);
		}
		//vTaskDelay(1);
	}
}
void can_hardware_init(void){
    can_frame_init(&can1.tx_msg);
    can_frame_init(&can1.rx_msg);

    xTaskCreate(can_recv_task, "recv can", 1024*2, (void*)&can1, configMAX_PRIORITIES, &can_recv_handle);

	ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
	ESP_LOGI(EXAMPLE_TAG, "Driver installed");
	ESP_ERROR_CHECK(twai_start());
	ESP_LOGI(EXAMPLE_TAG, "Driver started");
}
void can_hardware_deinit(void){
	ESP_ERROR_CHECK(twai_stop());
	ESP_LOGI(EXAMPLE_TAG, "Driver stopped");
	ESP_ERROR_CHECK(twai_driver_uninstall());
	ESP_LOGI(EXAMPLE_TAG, "Driver uninstalled");
}
static void can_frame_init(twai_message_t* p_frame){
    p_frame->data_length_code = 8;
}
static void can_send_impl(CAN_Hw* p_hw){
#if CAN_DEBUG
//	ESP_LOGI(EXAMPLE_TAG,"Can tx: %d\n",(int) p_hw->tx_msg.identifier);
//	ESP_LOG_BUFFER_HEX(EXAMPLE_TAG,p_hw->tx_msg.data,p_hw->tx_msg.data_length_code);
#endif
    twai_transmit(&p_hw->tx_msg,pdMS_TO_TICKS(1));
}
