#ifndef FLIPPIE_SERVER_H
#define FLIPPIE_SERVER_H

#include "handler/ui_handler.h"
#include "handler/dots_handler.h"
#include "handler/pixel_handler.h"
#include "handler/flippie_handler.h"
#include <ESP8266WebServer.h>


class FlippieServer {
public:
   FlippieServer(ESP8266WebServer s);
private:
   ESP8266WebServer server;
};

#endif
