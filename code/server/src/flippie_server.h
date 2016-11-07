#include "flippie.h"
#include "flippie_device.h"
#include <ESP8266WebServer.h>
#ifndef FLIPPIE_SERVER_H
#define FLIPPIE_SERVER_H

class FlippieServer {
private:
   ESP8266WebServer _server;
   FlippieDevice _flippie_device;
public:
   FlippieServer();
   void init(ESP8266WebServer server);
   void handleRoot();
   void handleSr();
   void handlePixel();
   void handleFlipdot();
   void handleDots();
};
#endif
