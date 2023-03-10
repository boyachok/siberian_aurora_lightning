
// /*
//  * Connect to WiFi. If no connection is made within WIFI_TIMEOUT, ESP gets resettet.
//  */
void wifi_setup() {
  DEBUG_PRINTLN();
  Serial.print("Connecting to ");
  DEBUG_PRINTLN(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.mode(WIFI_STA);
  #ifdef STATIC_IP  
    WiFi.config(ip, gateway, subnet);
  #endif

  unsigned long connect_start = millis();
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if(millis() - connect_start > WIFI_TIMEOUT) {
      DEBUG_PRINTLN();
      Serial.print("Tried ");
      Serial.print(WIFI_TIMEOUT);
      Serial.print("ms. Resetting ESP now.");
      ESP_RESET;
    }
  }

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");  
  Serial.print("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINTLN();
}


// /*
//  * Build <li> string for all modes.
//  */
void modes_setup() {
  modes = "";
  // uint8_t num_modes = sizeof(myModes) > 0 ? sizeof(myModes) : ws2812fx.getModeCount();
  // u8 num_modes = 2
  for(uint8_t i=0; i < 2; i++) {
    uint8_t m = sizeof(myModes) > 0 ? myModes[i] : i;
    modes += "<li><a href='#'>";
    modes += "CustomMode";
    modes += "</a></li>";
  }
}

// /* #####################################################
// #  Webserver Functions
// ##################################################### */

void srv_handle_not_found() {
  server.send(404, "text/plain", "File Not Found");
}

void srv_handle_index_html() {
  server.send_P(200,"text/html", index_html);
}

void srv_handle_main_js() {
  server.send_P(200,"application/javascript", main_js);
}

void srv_handle_modes() {
  server.send(200,"text/plain", modes);
}

void srv_handle_set() {
  for (uint8_t i=0; i < server.args(); i++){
    if(server.argName(i) == "c") {
      DEBUG_PRINTLN("c");

      // uint32_t tmp = (uint32_t) strtol(server.arg(i).c_str(), NULL, 10);
      // if(tmp <= 0xFFFFFF) {
      //   ws2812fx.setColor(tmp);
      // }
    }

    if(server.argName(i) == "m") {
      DEBUG_PRINTLN("m");
      // DEBUG_PRINTLN(new_mode);

      uint8_t tmp = (uint8_t) strtol(server.arg(i).c_str(), NULL, 10);
      uint8_t new_mode = sizeof(myModes) > 0 ? myModes[tmp % sizeof(myModes)] : tmp % 2;
      STRIP_MODE = new_mode;
      // ws2812fx.setMode(new_mode);
      // auto_cycle = false;
      // Serial.print("mode is "); DEBUG_PRINTLN(ws2812fx.getModeName(ws2812fx.getMode()));
    }

    if(server.argName(i) == "b") {
      DEBUG_PRINTLN("b");
      if(server.arg(i)[0] == '-') {
        strip_1.setBrightness(strip_1.getBrightness() * 0.8);
      } else if(server.arg(i)[0] == ' ') {
        strip_1.setBrightness(min(max(strip_1.getBrightness(), 5) * 1.2, 255));
      } else { // set brightness directly
        uint8_t tmp = (uint8_t) strtol(server.arg(i).c_str(), NULL, 10);
        strip_1.setBrightness(tmp);
      }
      Serial.print("brightness is "); DEBUG_PRINTLN(strip_1.getBrightness());
    }

    if(server.argName(i) == "s") {
      DEBUG_PRINTLN("s");
      // if(server.arg(i)[0] == '-') {
      //   ws2812fx.setSpeed(max(ws2812fx.getSpeed(), 5) * 1.2);
      // } else if(server.arg(i)[0] == ' ') {
      //   ws2812fx.setSpeed(ws2812fx.getSpeed() * 0.8);
      // } else {
      //   uint16_t tmp = (uint16_t) strtol(server.arg(i).c_str(), NULL, 10);
      //   ws2812fx.setSpeed(tmp);
      // }
      // Serial.print("speed is "); DEBUG_PRINTLN(ws2812fx.getSpeed());
    }

    if(server.argName(i) == "a") {
      DEBUG_PRINTLN("a");
      // if(server.arg(i)[0] == '-') {
      //   auto_cycle = false;
      // } else {
      //   auto_cycle = true;
      //   auto_last_change = 0;
      // }
    }
  }
  server.send(200, "text/plain", "OK");
}

void web_server_init() {
  server.on("/", srv_handle_index_html);
  server.on("/main.js", srv_handle_main_js);
  server.on("/modes", srv_handle_modes);
  server.on("/set", srv_handle_set);
  server.onNotFound(srv_handle_not_found);
  server.begin();
} 