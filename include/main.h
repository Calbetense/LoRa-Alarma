 #pragma once

/********** Includes ***********/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <esp_log.h>
#include <esp_sleep.h>

#include "lora.h"     

#include "driver/gpio.h"

/********** Defines ************/
#define GPIO_ALARMA 22

#define LIMIT_DO    4.5 // mg/L

/*Defines needed of LoRa Library*/
#define CONFIG_CS_GPIO      18
#define CONFIG_RST_GPIO     14
#define CONFIG_MISO_GPIO    19
#define CONFIG_MOSI_GPIO    27
#define CONFIG_SCK_GPIO     5

/*** Structures ***/
typedef enum {
    O2,
    Temp,
    Cont,
    Orp
}Id_t;

/* All the data will reach with an identifier */
typedef struct
{
    Id_t id;
    float data;
}Data_t;

/*** Declarations ***/

// LoRa
void lora_utils_init();
Data_t lora_utils_receive();
