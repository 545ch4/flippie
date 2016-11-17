#ifndef ABSTRACT_HANDLER_H
#define ABSTRACT_HANDLER_H

#include <ESP8266WebServer.h>

class AbstractHandler : public RequestHandler {
public:
   virtual bool canHandle(HTTPMethod method, String uri) override;
   virtual bool handle(ESP8266WebServer& server, HTTPMethod method, String uri) override;

   String argsToString(ESP8266WebServer& server);
   
};

#endif
