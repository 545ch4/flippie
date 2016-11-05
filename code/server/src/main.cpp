#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Flippie.h"
#include "functions.h"

#define DEBUG

flippie_t flippie_dev;
Flippie flippie;

const char* host = "flippie";
//const char* ssid = "network";
//const char* password = "forensicgenetics";
const char* ssid = "wlan";
const char* password = "oskarheleneheim";

ESP8266WebServer server(80);
MDNSResponder mdns;

void handleRoot() {
  server.send(200, "text/html",
#include "data/index.html"
  );
}

void handleSr() {
  bool sent = false;
  if(server.hasArg("led")) {
    flippie.paint_leds(
      server.arg("led").toInt() == 1 && server.arg("state").toInt() == 1 ? 1 : 0,
      server.arg("led").toInt() == 2 && server.arg("state").toInt() == 1 ? 1 : 0,
      server.arg("led").toInt() == 3 && server.arg("state").toInt() == 1 ? 1 : 0
    );
  } else if(server.hasArg("fp2800a_addr")) {
    unsigned int addr = server.arg("fp2800a_addr").toInt();
    flippie.set_address(255 & addr);
  } else if(server.hasArg("fp2800a_column")) {
    flippie.set_column(server.arg("fp2800a_column").toInt());
  } else if(server.hasArg("fp2800a_column_code")) {
    flippie.set_column_code(server.arg("fp2800a_column_code").toInt(), server.arg("state").toInt());
  } else if(server.hasArg("fp2800a_enable")) {
    flippie.set_enable(server.arg("state").toInt());
  } else if(server.hasArg("fp2800a_data")) {
    flippie.set_data(server.arg("state").toInt());
  } else if(server.hasArg("fp2800a_row_set_plusvs")) {
    flippie.set_row_plusvs(server.arg("fp2800a_row_set_plusvs").toInt());
  } else if(server.hasArg("fp2800a_row_set_gnd")) {
    flippie.set_row_gnd(server.arg("fp2800a_row_set_gnd").toInt());
  } else if(server.hasArg("clear")) {
    flippie.clear_shift_registers();
  } else {
    if(!sent) {
      Serial.printf("SR Unknown commane '%s'\n", server.argName(0).c_str());
      server.send(405, "text/html", "Unknown command");
    }
  }
  if(!sent) {
    Serial.printf("SR %s\n", server.argName(0).c_str());
    server.send(200, "text/html", "OK");
  }
}

void handlePixel() {
  flippie.fill_shift_register_and_fire(server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt(), FP2800A_ACTIVE_TIME_IN_USEC);
  Serial.printf("set pixel => row=%u, module=%u, column=%u, state=%u\n", server.arg("r").toInt(), server.arg("m").toInt(), server.arg("c").toInt(), server.arg("state").toInt());
  server.send(200, "text/html", "OK");
}

void handleFlipdot() {
  bool sent = false;
  if(server.arg("task").equals("clear")) {
    flippie.clear();
  } else if(server.arg("task").equals("fill")) {
    flippie.fill();
  } else if(server.arg("task").equals("inverse")) {
    flippie.inverse();
  } else if(server.arg("task").equals("magnitize")) {
    flippie.magnitize(server.arg("state").toInt(), server.arg("duration").toInt());
  } else {
    if(!sent) {
      Serial.printf("FLIPDOT Unknown command '%s'\n", server.arg("task").c_str());
      server.send(500, "text/html", "Unknown command");
    }
  }
  if(!sent) {
    Serial.printf("FLIPDOT %s\n", server.arg("task").c_str());
    server.send(200, "text/html", "OK");
  }
}

void handleDots() {
  if(server.hasArg("dots")) {
    unsigned int ptr, u;
    String dots = server.arg("dots");
    const char * dots_c_str = dots.c_str();
    // hex encoded post data
    if(dots.length() != flippie.rows * flippie.modules * sizeof(unsigned int) * 2) {
      Serial.printf("Size mismatch: 'dots' is %u instead of %u bytes (%u rows X %u modules X %u bytes X 2) long!\n", dots.length(), flippie.rows * flippie.modules * sizeof(unsigned int) * 2, flippie.rows, flippie.modules, sizeof(unsigned int));
    }
#ifdef DEBUG
    Serial.printf("dots(%i)=%s\n", dots.length(), dots_c_str);
#endif
    ptr = 0;
    byte * dots_bytes = (byte *)malloc((dots.length() / 2) * sizeof(byte));
    for(unsigned int i = 0; i < dots.length(); i += 2) {
#ifdef DEBUG
      sscanf(&dots_c_str[i], "%2hhx", &u);
#endif
      dots_bytes[ptr] = u;
      ptr++;
    }

#ifdef DEBUG
    Serial.print("\ndots(int)=[ ");
#endif
    unsigned int ** int_dots = (unsigned int **)malloc(flippie_dev.num_rows * sizeof(unsigned int *));
    ptr = 0;
    for(unsigned int i = 0; i < flippie_dev.num_rows; ++i) {
      int_dots[i] = (unsigned int *)malloc(flippie_dev.num_modules * sizeof(unsigned int));
      for(unsigned int j = 0; j < flippie_dev.num_modules; ++j) {
//        for(unsigned int k = 4; --k > 0;) {
//        for(unsigned int k = 0; k < 4; ++k) {
#ifdef DEBUG
          Serial.printf("(%u,%u,%u,%u) ", dots_bytes[ptr], dots_bytes[ptr + 1], dots_bytes[ptr + 2], dots_bytes[ptr + 3]);
#endif
          int_dots[i][j] = (dots_bytes[ptr]) | (dots_bytes[ptr + 1]<<8) | (dots_bytes[ptr + 2]<<16) | (dots_bytes[ptr + 3]<<24);
          ptr += 4;
//        }
      }
    }
#ifdef DEBUG
    Serial.println("]");

    for(unsigned int i = 0; i < flippie_dev.num_rows; ++i) {
      for(unsigned int j = 0; j < flippie_dev.num_modules; ++j) {
        Serial.printf("%010u | ", int_dots[i][j]);
      }
      Serial.print("\n");
    }

    for(unsigned int i = 0; i < flippie_dev.num_rows; ++i) {
      for(unsigned int j = 0; j < flippie_dev.num_modules; ++j) {
        for(unsigned int k = 0; k < flippie_dev.num_columns[j]; ++k) {
           Serial.print(((int_dots[i][j] & 1<<k) == 1<<k) ? '*' : ' ');
        }
      }
      Serial.println();
    }
#endif

    flippie.paint(int_dots);
    server.send(200, "text/html", "OK");
  } else {
    handleRoot();
  }
}

void setup(void){
  ESP.wdtEnable(WDTO_8S);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting...");

  flippie_dev.num_modules = 4;
  flippie_dev.addresses = new unsigned int[4]{1, 2, 4, 8};
  flippie_dev.num_rows = 18;
  flippie_dev.num_columns = new unsigned int[4]{28, 28, 28, 21};
  flippie_dev.sr_set_row_gnd_pins = new unsigned int[20]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  flippie_dev.sr_set_row_plusvs_pins = new unsigned int[20]{20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
  flippie_dev.sr_column_code_pins = new unsigned int[5]{44, 43, 42, 41, 40};
  flippie_dev.sr_address_pins = new unsigned int[7]{45, 46, 47, 48, 49, 50, 51};
  flippie_dev.sr_data_pin = 52;
  flippie_dev.sr_led1_pin = 53;
  flippie_dev.sr_led2_pin = 54;
  flippie_dev.sr_led3_pin = 55;
  flippie_dev.clock_pin = 16; // GPIO16
  flippie_dev.latch_pin = 14; // GPIO14
  flippie_dev.serial_data_pin = 5; //GPIO5
  flippie_dev.clear_pin = 13; // GPIO13
  flippie_dev.output_enable_pin = 12; // GPIO12
  flippie_dev.address_enable_pin = 4; // GPIO4
  flippie.init(flippie_dev);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if (mdns.begin("flippie", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/sr", handleSr);
  server.on("/pixel", handlePixel);
  server.on("/flipdot", handleFlipdot);
  server.on("/dots", handleDots);

  server.begin();
  mdns.addService("http", "tcp", 80);

  Serial.printf("Ready! Open http://%s in your browser\n", WiFi.localIP().toString().c_str());
  Serial.print("\n");
}

void loop(void){
  ESP.wdtEnable(WDTO_8S);
  server.handleClient();
}
