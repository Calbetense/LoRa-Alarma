/*
    Alarma: Gets the LoRa message getting the DO value. If it's below a given value makes the alarm yell.
*/


#include "main.h"

const char* TAG = "MAIN";

void main_task(void *p){


    //Declarations
    Data_t toSend;

    while (1)
    {
        vTaskDelay(50);

        toSend = lora_utils_receive();
        if(toSend.id == 404) continue;

        switch(toSend.id){
            case O2:
                if(toSend.data < LIMIT_DO){
                    gpio_set_level(GPIO_NUM_22, 1);
                }
                break;
            case Temp:
                break;
            case Cont:
                break; 
            case Orp:
                break; 
            default: 
            break;
        }

        ESP_LOGI(TAG, "\n Dissolved Oxygen = %f mg/L \n", toSend.data);

    }
    
}

void app_main() {
    
    lora_utils_init();

    //GPIO configuration
    gpio_config_t gpio_conf = {
        //disable interrupts
        .intr_type = GPIO_INTR_DISABLE,
        //set output mode
        .mode = GPIO_MODE_OUTPUT,
        //bit mask of the pins you want to set
        .pin_bit_mask = (1ULL << GPIO_ALARMA),
        //disable pull up and pull down
        .pull_down_en = 0,
        .pull_up_en   = 0
    };

    gpio_config(&gpio_conf);

    gpio_set_level(GPIO_NUM_22, 0);

    #ifdef DEBUG
    ESP_LOGI(TAG, "Everything's init. (Teorically)");
    #endif

    xTaskCreate(main_task, "main", 2048, NULL, 1, NULL);

    vTaskDelete(NULL);
}