#include "flippie.h"
#include "flippie_device.h"
#include "flippie_server.h"
#include <ESP8266WebServer.h>

#define DEBUG true

void FlippieServer::init(ESP8266WebServer server) {
   FlippieDevice _flippie_device;
   _server = server;
   _server.on("/", this->*handleRoot);
   _server.on("/sr", this->*handleSr);
   _server.on("/pixel", this->*handlePixel);
   _server.on("/flipdot", this->*handleFlipdot);
   _server.on("/dots", this->*handleDots);
}

void FlippieServer::handleRoot() {
  _server.send(200, "text/html",
#include "data/index.html"
  );
}

void FlippieServer::handleSr() {
  bool sent = false;
  if(_server.hasArg("led")) {
    _flippie_device.f.paint_leds(
      _server.arg("led").toInt() == 1 && _server.arg("state").toInt() == 1 ? 1 : 0,
      _server.arg("led").toInt() == 2 && _server.arg("state").toInt() == 1 ? 1 : 0,
      _server.arg("led").toInt() == 3 && _server.arg("state").toInt() == 1 ? 1 : 0
    );
  } else if(_server.hasArg("fp2800a_addr")) {
    unsigned int addr = _server.arg("fp2800a_addr").toInt();
    _flippie_device.f.set_address(255 & addr);
  } else if(_server.hasArg("fp2800a_column")) {
    _flippie_device.f.set_column(_server.arg("fp2800a_column").toInt());
  } else if(_server.hasArg("fp2800a_column_code")) {
    _flippie_device.f.set_column_code(_server.arg("fp2800a_column_code").toInt(), _server.arg("state").toInt());
  } else if(_server.hasArg("fp2800a_enable")) {
    _flippie_device.f.set_enable(_server.arg("state").toInt());
  } else if(_server.hasArg("fp2800a_data")) {
    _flippie_device.f.set_data(_server.arg("state").toInt());
  } else if(_server.hasArg("fp2800a_row_set_plusvs")) {
    _flippie_device.f.set_row(_server.arg("fp2800a_row_set_plusvs").toInt());
  } else if(_server.hasArg("fp2800a_row_set_gnd")) {
    _flippie_device.f.rst_row(_server.arg("fp2800a_row_set_gnd").toInt());
  } else if(_server.hasArg("clear")) {
    _flippie_device.f.clear_shift_registers();
  } else {
    if(!sent) {
      Serial.printf("SR Unknown commane '%s'\n", _server.argName(0).c_str());
      _server.send(405, "text/html", "Unknown command");
    }
  }
  if(!sent) {
    Serial.printf("SR %s\n", _server.argName(0).c_str());
    _server.send(200, "text/html", "OK");
  }
}

void FlippieServer::handlePixel() {
  _flippie_device.f.fill_shift_register_and_fire(_server.arg("r").toInt(), _server.arg("m").toInt(), _server.arg("c").toInt(), _server.arg("state").toInt(), FP2800A_ACTIVE_TIME_IN_USEC);
  Serial.printf("set pixel => row=%u, module=%u, column=%u, state=%u\n", _server.arg("r").toInt(), _server.arg("m").toInt(), _server.arg("c").toInt(), _server.arg("state").toInt());
  _server.send(200, "text/html", "OK");
}

void FlippieServer::handleFlipdot() {
  bool sent = false;
  if(_server.arg("task").equals("clear")) {
    _flippie_device.f.clear();
  } else if(_server.arg("task").equals("fill")) {
    _flippie_device.f.fill();
  } else if(_server.arg("task").equals("inverse")) {
    _flippie_device.f.inverse();
  } else if(_server.arg("task").equals("magnitize")) {
    _flippie_device.f.magnetize(_server.arg("state").toInt(), _server.arg("duration").toInt());
  } else {
    if(!sent) {
      Serial.printf("FLIPDOT Unknown command '%s'\n", _server.arg("task").c_str());
      _server.send(500, "text/html", "Unknown command");
    }
  }
  if(!sent) {
    Serial.printf("FLIPDOT %s\n", _server.arg("task").c_str());
    _server.send(200, "text/html", "OK");
  }
}

void FlippieServer::handleDots() {
  if(_server.hasArg("dots")) {
    unsigned int ptr, u;
    String dots = _server.arg("dots");
    const char * dots_c_str = dots.c_str();
    // hex encoded post data
    if(dots.length() != _flippie_device.f.rows * _flippie_device.f.modules * sizeof(unsigned int) * 2) {
      Serial.printf("Size mismatch: 'dots' is %u instead of %u bytes (%u rows X %u modules X %u bytes X 2) long!\n", dots.length(), _flippie_device.f.rows * _flippie_device.f.modules * sizeof(unsigned int) * 2, _flippie_device.f.rows, _flippie_device.f.modules, sizeof(unsigned int));
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

    _flippie_device.f.paint(int_dots);
    _server.send(200, "text/html", "OK");
  } else {
    handleRoot();
  }
}
