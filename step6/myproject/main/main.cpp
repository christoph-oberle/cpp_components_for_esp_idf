#include "esp_log.h"
#include "wifi_manager.hpp"
#include "deep_sleep.hpp"
RTC_DATA_ATTR int bootCount = 0;
#include "freertos/task.h"

static char tag[] = "myproject";

extern "C" void app_main(void)
{
    /* Delay to reconnect terminal after Wakeup */
    vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 msec

    ESP_LOGI(tag, "Start");

    /* Deep Sleep: Initialize DeepSleep class */
    ESP_LOGI(tag, "DeepSleep");
    DeepSleep deepSleep(
		std::string("DeepSleep"), // tag
		&bootCount // Address of int bootCount in RTC_DATA
    );

    /* Deep Sleep: show bootCount */
    ESP_LOGI(tag, "bootCount: %i", bootCount);

    /* Deep Sleep: Retrieve the Wakeup reason */
    ESP_LOGI(tag, "GetWakeupReason");
    esp_sleep_wakeup_cause_t wakeupReason = deepSleep.GetWakeupReason();

    switch(wakeupReason) {
        case ESP_SLEEP_WAKEUP_EXT0 : ESP_LOGI(tag, "Wakeup caused by external signal using RTC_IO"); break;
        case ESP_SLEEP_WAKEUP_EXT1 : ESP_LOGI(tag, "Wakeup caused by external signal using RTC_CNTL"); break;
        case ESP_SLEEP_WAKEUP_TIMER : ESP_LOGI(tag, "Wakeup caused by timer"); break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD : ESP_LOGI(tag, "Wakeup caused by touchpad"); break;
        case ESP_SLEEP_WAKEUP_ULP : ESP_LOGI(tag, "Wakeup caused by ULP program"); break;
        case ESP_SLEEP_WAKEUP_GPIO : ESP_LOGI(tag, "Wakeup caused by gpio"); break;
        default : ESP_LOGI(tag, "Wakeup was not caused by deep sleep: %d",wakeupReason); break;
    }

    /* Wi-Fi: Initialize WifiManager class */
    ESP_LOGI(tag, "WifiManager");
    Wifi wifi(
		std::string("WifiManager"), // tag
		std::string("ESP32"), // ssid_prefix
		std::string("de-DE") // language
    );

    /* Wi-Fi: Wait until Wi-Fi is connected */
    ESP_LOGI(tag, "Wifi is %s", wifi.IsConnected() ? "connected" : "not connected");

    /* Wi-Fi: Retrieve connection information */
    ESP_LOGI(tag, "Ssid: %s", wifi.GetSsid().c_str());
    ESP_LOGI(tag, "IpAddress: %s", wifi.GetIpAddress().c_str());
    ESP_LOGI(tag, "Rssi: %i", wifi.GetRssi());
    ESP_LOGI(tag, "Channel: %i", wifi.GetChannel());
    ESP_LOGI(tag, "MacAddress: %s", wifi.GetMacAddress().c_str());

    /* here the "real" work is done! */

    /* Deep Sleep: Configure the Wakeup Sources */
    ESP_LOGI(tag, "EnableTimerWakeup");
    ESP_ERROR_CHECK(deepSleep.EnableTimerWakeup(30, "sec"));  // enable wake up after 30 seconds sleep time

    ESP_LOGI(tag, "EnableGpioWakeup");
        ESP_ERROR_CHECK(deepSleep.EnableGpioWakeup((gpio_num_t) 0, 1));  // enable wake up when GPIO 0 is pulled up
    ESP_LOGI(tag, "End");

    /* Deep Sleep: Go to Deep Sleep */
    bool rc = false;
    ESP_LOGI(tag, "GoToDeepSleep");
    rc = deepSleep.GoToDeepSleep(); // go to deep sleep

    // this statement will not be reached, if GoToDeepSleep is working
    ESP_LOGI(tag, "GoToDeepSleep rc=%u", rc);
}
