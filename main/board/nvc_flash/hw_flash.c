/*
 * hw_flash.c
 *
 *  Created on: Sep 22, 2022
 *      Author: Admin
 */


#include "hw_flash.h"

#define STORE_KEY "storage"

nvs_handle_t flash_handle;

void flash_init(void){
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
	ret = nvs_open(STORE_KEY, NVS_READWRITE, &flash_handle);
	if(ret != ESP_OK){
		//return ;
	}
	//ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK( ret );
}
void flash_erase_key(const char* key){
	nvs_open(STORE_KEY, NVS_READWRITE, &flash_handle);
	nvs_erase_key(flash_handle, key);
	nvs_commit(flash_handle);
	nvs_close(flash_handle);
}
void flash_erase(void){
    ESP_ERROR_CHECK(nvs_flash_erase());
    esp_err_t ret = nvs_flash_init();
    ESP_ERROR_CHECK( ret );
}
int flash_write_str(const char* key,const char* value){
	nvs_open(STORE_KEY, NVS_READWRITE, &flash_handle);
	esp_err_t ret = nvs_set_str(flash_handle, key, value);
	if(ret != ESP_OK){
		return ret;
	}
	nvs_commit(flash_handle);
	nvs_close(flash_handle);
	return ret;
}
int flash_read_str(const char* key,char* value){
	esp_err_t ret;
	nvs_open(STORE_KEY, NVS_READWRITE, &flash_handle);
	size_t size = -1;
	ret = nvs_get_str(flash_handle, key, value, &size);
	if(ret != ESP_OK){
		return -1;
	}

	nvs_close(flash_handle);
	return (int)size;
}
