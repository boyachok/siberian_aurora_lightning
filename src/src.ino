#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WS2812FX.h>

#include "src.h"
// #include "led_strip/led_strip.cpp"

#define WEB_SERVER ESP8266WebServer
#define ESP_RESET ESP.reset()

extern const char index_html[];
extern const char main_js[];


//#define STATIC_IP                       // uncomment for static IP, set IP below
#ifdef STATIC_IP
  IPAddress ip(192,168,0,123);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
#endif

// QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

unsigned long auto_last_change = 0;
unsigned long last_wifi_check_time = 0;
String modes = "";
uint8_t myModes[] = {}; // *** optionally create a custom list of effect/mode numbers
bool auto_cycle = false;

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_BRG + NEO_KHZ800);
WEB_SERVER server(HTTP_PORT);

void setup(){
  Serial.begin(115200);
  delay(500);
  DEBUG_PRINTLN("\n\nStarting...");

  modes.reserve(5000);
  modes_setup();

  DEBUG_PRINTLN("WS2812FX setup");
  ws2812fx.init();
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.setColor(0xFF5900);
  ws2812fx.setSpeed(1000);
  ws2812fx.setBrightness(128);
  ws2812fx.start();

  DEBUG_PRINTLN("Wifi setup");
  wifi_setup();
 
  DEBUG_PRINTLN("HTTP server setup");
  web_server_init();
  DEBUG_PRINTLN("HTTP server started.");
  intital_led_strip_effect();
}


void loop() {
  unsigned long now = millis();
  server.handleClient();
  ws2812fx.service();
  led_strip_tick(now);
}
