/*
 * hw_flash.h
 *
 *  Created on: Sep 22, 2022
 *      Author: Admin
 */

#ifndef MAIN_BOARD_NVC_FLASH_HW_FLASH_H_
#define MAIN_BOARD_NVC_FLASH_HW_FLASH_H_

#include "nvs_flash.h"

void flash_init(void);
void flash_erase(void);

int flash_write_str(const char* key,const char* value);
int flash_read_str(const char* key,char* value);
void flash_erase_key(const char* key);
#endif /* MAIN_BOARD_NVC_FLASH_HW_FLASH_H_ */
