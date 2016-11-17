#include "abstract_handler.h"

String AbstractHandler::argsToString(ESP8266WebServer& server) {
   char* tmp = (char*)malloc(1024);
   unsigned int tmp_i = 0, j;
   for(unsigned int i = 0; i < server.args(); i++) {
      if(i > 0) {
         tmp[tmp_i++] = '&';
      }
      j = server.argName(i).length();
      memcpy(tmp + tmp_i, server.argName(i).c_str(), j);
      tmp_i += j;

      tmp[tmp_i++] = '=';

      j = server.arg(i).length();
      memcpy(tmp + tmp_i, server.arg(i).c_str(), j);
      tmp_i += j;
   }
   tmp[tmp_i] = '\0';
   String s(tmp);
   free(tmp);
   return s;
}
