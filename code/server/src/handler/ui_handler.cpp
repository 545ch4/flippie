#include "ui_handler.h"

UIHandler::UIHandler(Flippie* f) {
   flippie = f;
   root_page =
#include "data/index.html"
;
   char *config_page_temp;
   config_page_temp = (char *)malloc(1024 * sizeof(char));
   unsigned int i = 0;
   i = sprintf(config_page_temp + i, "{\n\t\"rows\": %u,\n\t\"columns\": [\n", flippie->config->num_rows);
   for(int j = 0; j < flippie->config->num_modules - 1; j++) {
      i += sprintf(config_page_temp + i, "\t\t%u,\n", flippie->config->num_columns[j]);
   }

   i += sprintf(config_page_temp + i, "\t\t%u\n\t]\n}\n\0", flippie->config->num_columns[flippie->config->num_modules - 1]);
   config_page = String(config_page_temp);
   free(config_page_temp);
}

bool UIHandler::handle(ESP8266WebServer& server, HTTPMethod method, String uri) {
   if (method != HTTP_GET) {
      return false;
   }
   if(uri == "/" || strncmp("/ui", uri.c_str(), 3) == 0) {
      if(uri == "/" || uri == "/index.html") {
         server.sendHeader("Location", "/ui/", true);
         server.send(302, "text/html", "");
      } else if(uri == "/ui" || uri == "/ui/" || uri == "/ui/index.html") {
         server.send(200, "text/html", root_page);
      } else if(uri == "/ui/config.json") {
         server.send(200, "application/json", config_page);
      }
      return true;
   }
   return false;
}
bool UIHandler::canHandle(HTTPMethod method, String uri) {
   if (method == HTTP_GET && (uri == "/" || strncmp("/ui", uri.c_str(), 3) == 0)) {
      return true;
   }
   return false;
}
