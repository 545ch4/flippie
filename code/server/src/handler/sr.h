#ifndef HANDLER_SR_H
#define HANDLER_SR_H
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

class SrPage : public RequestHandler {
public:
  SrPage(const char* uri, FlippieDevice flippie);
  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
protected:
  String _uri;
  Flippie flippie;
};

#endif
