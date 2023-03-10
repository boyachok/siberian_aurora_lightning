#include "src.h"

void intital_led_strip_effect() {
    for (u8 i = 0; i < LED_COUNT; i++) {
        strip_1.setPixelColor(i, 0x111111); 
        strip_1.show();
        delay(100);
    }
}

void led_mode_0_tick(){
    strip_1.fill(0xffffff); 
    strip_1.show();
    delay(1000);
}
void led_mode_1_tick(){
    strip_1.fill(0xaaaaaa); 
    strip_1.show();
    delay(1000);
}
// void led_strip_tick(unsigned long now) {
//   if(now - last_wifi_check_time > WIFI_TIMEOUT) {
//       DEBUG_PRINTLN("Checking WiFi... ");
//       if(WiFi.status() != WL_CONNECTED) {
//       DEBUG_PRINTLN("WiFi connection lost. Reconnecting...");
//       wifi_setup();
//       } else {
//       DEBUG_PRINTLN("OK");
//       }
//       last_wifi_check_time = now;
//   }

//   if(auto_cycle && (now - auto_last_change > 10000)) { // cycle effect mode every 10 seconds
//       uint8_t next_mode = (ws2812fx.getMode() + 1) % ws2812fx.getModeCount();
//       if(sizeof(myModes) > 0) { // if custom list of modes exists
//       for(uint8_t i=0; i < sizeof(myModes); i++) {
//           if(myModes[i] == ws2812fx.getMode()) {
//           next_mode = ((i + 1) < sizeof(myModes)) ? myModes[i + 1] : myModes[0];
//           break;
//           }
//       }
//       }
//       ws2812fx.setMode(next_mode);
//       DEBUG_PRINTLN("mode is "); 
//       DEBUG_PRINTLN(ws2812fx.getModeName(ws2812fx.getMode()));
//       auto_last_change = now;
//     }
// }