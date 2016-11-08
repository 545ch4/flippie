#ifndef FLIPPIE_SERVER_H
#define FLIPPIE_SERVER_H

#include "handler/dots.h"
#include "handler/flip_dot.h"
#include "handler/pixel.h"
#include "handler/root.h"
#include "handler/sr.h"
#include <ESP8266WebServer.h>


class FlippieServer {
public:
   FlippieServer(ESP8266WebServer s);
private:
   ESP8266WebServer server;
};

#endif
