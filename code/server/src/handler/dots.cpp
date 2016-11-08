#include "dots.h"
#include "../flippie.h"
#include "../flippie_device.h"
#include <ESP8266WebServer.h>

DotsPage::DotsPage(const char* uri, FlippieDevice f) : _uri(uri) {
   flippie = f;
}

bool DotsPage::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
   if (requestMethod != HTTP_GET || requestUri != _uri) {
      return false;
   }
   if(server.hasArg("dots")) {
     unsigned int ptr, u;
     String dots = server.arg("dots");
     const char * dots_c_str = dots.c_str();
     // hex encoded post data
     if(dots.length() != flippie.config.num_rows * flippie.config.num_modules * sizeof(unsigned int) * 2) {
       Serial.printf("Size mismatch: 'dots' is %u instead of %u bytes (%u rows X %u modules X %u bytes X 2) long!\n", dots.length(), flippie.config.num_rows * flippie.config.num_modules * sizeof(unsigned int) * 2, flippie.config.num_rows, flippie.config.num_modules, sizeof(unsigned int));
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
     unsigned int ** int_dots = (unsigned int **)malloc(flippie.config.num_rows * sizeof(unsigned int *));
     ptr = 0;
     for(unsigned int i = 0; i < flippie.config.num_rows; ++i) {
       int_dots[i] = (unsigned int *)malloc(flippie.config.num_modules * sizeof(unsigned int));
       for(unsigned int j = 0; j < flippie.config.num_modules; ++j) {
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

     for(unsigned int i = 0; i < flippie.config.num_rows; ++i) {
       for(unsigned int j = 0; j < flippie.config.num_modules; ++j) {
         Serial.printf("%010u | ", int_dots[i][j]);
       }
       Serial.print("\n");
     }

     for(unsigned int i = 0; i < flippie.config.num_rows; ++i) {
       for(unsigned int j = 0; j < flippie.config.num_modules; ++j) {
         for(unsigned int k = 0; k < flippie.config.num_columns[j]; ++k) {
            Serial.print(((int_dots[i][j] & 1<<k) == 1<<k) ? '*' : ' ');
         }
       }
       Serial.println();
     }
 #endif

     flippie.paint(int_dots);
     server.send(200, "text/html", "OK");
   } else {
     return false;
   }
   return true;
}
