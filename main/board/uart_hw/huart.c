/*
 * huart.c
 *
 *  Created on: Dec 20, 2022
 *      Author: Admin
 */


#include "huart.h"
#include "esp_log.h"
static const char *TAG = "UART";
#define BUF_SIZE (1024)
#define RD_BUF_SIZE (BUF_SIZE)
#define PATTERN_CHR_NUM    (3)

static void uart_event_task(void *pvParameters);

void HAL_UART_Init(UART_Typedef *huart){
    uart_config_t uart_config = {
        .baud_rate = huart->baurate,
        .data_bits = huart->databit,
        .parity = huart->parity,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(huart->port, BUF_SIZE * 2, BUF_SIZE * 2, 20,&huart->queue, 0);
    uart_param_config(huart->port, &uart_config);
    uart_set_pin(huart->port, huart->pin_tx, huart->pin_rx, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_enable_pattern_det_baud_intr(huart->port, '+', PATTERN_CHR_NUM, 9, 0, 0);
    uart_pattern_queue_reset(huart->port, 20);
    xTaskCreate(uart_event_task, "uart_event_task", 1024*2,(void*)huart, 21, NULL);
}
int HAL_UART_Transmit(UART_Typedef *huart,uint8_t *data,uint32_t len){
	return uart_write_bytes(huart->port,data,len);
}
int HAL_UART_Receive(UART_Typedef *huart,uint8_t *data,uint32_t len){
	return uart_read_bytes(huart->port, data, len, (TickType_t)portMAX_DELAY);
}
int HAL_UART_Available(UART_Typedef *huart){
	size_t len = 0;
	uart_get_buffered_data_len(huart->port, &len);
	return (int)len;
}

static void uart_event_task(void *pvParameters){
	UART_Typedef *huart = (UART_Typedef*)pvParameters;
    uart_event_t event;
    size_t buffered_size;
    uint8_t dtmp[RD_BUF_SIZE];
    for(;;) {
        //Waiting for UART event.
        if(xQueueReceive(huart->queue, (void * )&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            //ESP_LOGI(TAG, "uart[%d] event:", huart->port);
            switch(event.type) {
                //Event of UART receving data
                /*We'd better handler data event fast, there would be much more data events than
                other types of events. If we take too much time on data event, the queue might
                be full.*/
                case UART_DATA:
                    //ESP_LOGI(TAG, "[UART DATA]: ");
                    uart_read_bytes(huart->port, dtmp, event.size, portMAX_DELAY);
                    //ESP_LOG_BUFFER_HEX(TAG,dtmp,event.size);
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(huart->port);
                    xQueueReset(huart->queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    // If buffer full happened, you should consider increasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(huart->port);
                    xQueueReset(huart->queue);
                    break;
                //Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                //Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                //UART_PATTERN_DET
                case UART_PATTERN_DET:
                    uart_get_buffered_data_len(huart->port, &buffered_size);
                    int pos = uart_pattern_pop_pos(huart->port);
                    ESP_LOGI(TAG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                    if (pos == -1) {
                        // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                        // record the position. We should set a larger queue size.
                        // As an example, we directly flush the rx buffer here.
                        uart_flush_input(huart->port);
                    } else {
                        uart_read_bytes(huart->port, dtmp, pos, 100 / portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_CHR_NUM + 1];
                        memset(pat, 0, sizeof(pat));
                        uart_read_bytes(huart->port, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
                        ESP_LOGI(TAG, "read data: %s", dtmp);
                        ESP_LOGI(TAG, "read pat : %s", pat);
                    }
                    break;
                //Others
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    vTaskDelete(NULL);
}

UART_Typedef huart1 = {.databit = DATA_8,.parity = PARITY_NONE,.pin_tx =21,.pin_rx =22,.port = 1,.baurate = 115200};
UART_Typedef huart2 = {.databit = DATA_8,.parity = PARITY_NONE,.pin_tx =16,.pin_rx =17,.port = 2,.baurate = 115200};
