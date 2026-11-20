#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_25    // Change if needed
#define buzzer_GPIO GPIO_NUM_26 // Change if needed

void led_blink_task(void *pvParameters);

static const char *TAG = "LED_BLINK";

/* ---------------- LED Blink Task ---------------- */
void led_blink_task(void *pvParameters)
{
    while (1)
    {
        gpio_set_level(LED_GPIO, 1); // LED ON
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(pdMS_TO_TICKS(800)); // 500 ms delay

        gpio_set_level(LED_GPIO, 0); // LED OFF
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(pdMS_TO_TICKS(800)); // 500 ms delay
    }
    vTaskDelay(pdMS_TO_TICKS(10)); // 500 ms delay
}
void playBuzzer(void *pvParameters)
{
    while (1)
    {
        gpio_set_level(buzzer_GPIO, 1); // Buzzer ON
        ESP_LOGI(TAG, "Buzzer ON");
        vTaskDelay(pdMS_TO_TICKS(800)); // 500 ms delay

        gpio_set_level(buzzer_GPIO, 0); // Buzzer OFF
        ESP_LOGI(TAG, "Buzzer OFF");
        vTaskDelay(pdMS_TO_TICKS(800)); // 500 ms delay
    }
    vTaskDelay(pdMS_TO_TICKS(10)); // 500 ms delay
}

// You can add another task here for counting and displaying numbers on the OLED as per your requirement.
/* ---------------- Main Function ---------------- */
void app_main(void)
{
    // Configure LED GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "Starting LED Blink Task");
    // Create LED task
    xTaskCreate(
        led_blink_task, // Task function
        "LED_Task",     // Task name
        2048,           // Stack size (bytes)
        NULL,           // Parameters
        5,              // Priority
        NULL            // Task handle
    );
    ESP_LOGI(TAG, "Starting Buzzer Task");
    xTaskCreate(
        playBuzzer,    // Task function
        "Buzzer_Task", // Task name
        2048,          // Stack size (bytes)
        NULL,          // Parameters
        4,             // Priority
        NULL           // Task handle
    );

    // for loop to count in 1 seec.
        for (int i = 0; i <= 100; i++)
        {
            ESP_LOGI(TAG, "Count: %d", i);
            vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second delay
        }

    // create A task which count and display on OLED numbers in each .5 second untill 100 and then reset
}