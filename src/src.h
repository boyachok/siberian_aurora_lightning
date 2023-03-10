#define DEBUG 1

#define DEBUG_PRINTLN(x)  if (DEBUG) { Serial.println (x); }

#define LED_STRIP_1_PIN 2
#define LED_STRIP_1_COUNT 60

#define LED_STRIP_2_PIN 3
#define LED_STRIP_2_COUNT 60

#define LED_STRIP_3_PIN 4
#define LED_STRIP_3_COUNT 60

#define WIFI_SSID "HUAWEI-D1CC"
#define WIFI_PASSWORD "13331154"

#define LED_PIN 4                       // 0 = GPIO0, 2=GPIO2
#define LED_COUNT 60

#define WIFI_TIMEOUT 30000              // checks WiFi every ...ms. Reset after this time, if WiFi cannot reconnect.
#define HTTP_PORT 80
