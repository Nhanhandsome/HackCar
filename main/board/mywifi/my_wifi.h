/*
 * wifi.h
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */

#ifndef COMPONENTS_WIFI_MY_WIFI_H_
#define COMPONENTS_WIFI_MY_WIFI_H_


#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_smartconfig.h"
#include "esp_wpa2.h"
#include "esp_system.h"
#include "esp_netif.h"

#define MODE_AP_STA 1
#define WIFI_SSID_DEFAULT "SSIDDEFAULT"
#define WIFI_PASS_DEFAULT "PASSDEFAULT"
#define WIFI_SETTING_SSID "wifi_ssid"
#define WIFI_SETTING_PWD "wifi_pwd"

//void wifi_hw_scan(void);
void wifi_initialise(void);
wifi_event_t get_wifi_status(void);
bool wifi_set_infor(char *ssid,char *pass);
void wifi_clear_info();
#endif /* COMPONENTS_WIFI_MY_WIFI_H_ */
