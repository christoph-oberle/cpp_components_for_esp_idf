#include "esp_log.h"

static char tag[] = "myproject";

extern "C" void app_main(void)
{
    ESP_LOGI(tag, "Start");

    /* here the "real" work is done! */

    ESP_LOGI(tag, "End");
}
