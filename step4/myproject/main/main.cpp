#include "esp_log.h"
#include "wifi_manager.hpp"

static char tag[] = "myproject";

extern "C" void app_main(void)
{
    ESP_LOGI(tag, "Start");

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

    ESP_LOGI(tag, "End");
}
