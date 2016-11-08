#ifndef HANDLER_ROOT_H
#define HANDLER_ROOT_H
#include <ESP8266WebServer.h>

class RootPage : public RequestHandler {
  public:
    RootPage(const char* uri) : _uri(uri) {};
    bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
  protected:
    String _uri;
};

#endif
