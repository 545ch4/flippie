#ifndef PIXEL_HANDLER_H
#define PIXEL_HANDLER_H
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

class PixelHandler : public RequestHandler {
public:
  PixelHandler(const char* uri, FlippieDevice flippie);
  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
protected:
  String _uri;
  Flippie flippie;
};

#endif
