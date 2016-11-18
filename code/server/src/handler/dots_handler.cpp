#include "dots_handler.h"

DotsHandler::DotsHandler(Flippie *f) { flippie = f; }

bool DotsHandler::handle(ESP8266WebServer &server, HTTPMethod method, String uri) {
   if (!canHandle(method, uri)) {
      return false;
   }
   
   debug_printf("Handle '%s' ? '%s' (%s) in DotsHandler...", uri.c_str(), argsToString(server).c_str(), method == HTTP_GET ? "GET" : "POST");
   
   if (method == HTTP_POST && server.hasArg("dots")) {
      String dots = server.arg("dots");
      unsigned char *dots_bytes = (unsigned char *)malloc(dots.length() * sizeof(unsigned char));
      unsigned int dots_bytes_length = dots.length(), i = 0, j = 0, k = 0;
      char *dots_string = (char *)malloc(dots.length());
      memcpy(dots_string, dots.c_str(), dots.length());
      
      b64.decode(dots_string, dots.length(), dots_bytes, &dots_bytes_length);
      
      if (dots_bytes_length != (flippie->config->num_rows * flippie->config->num_modules * 4)) {
         char *tmp = (char*)malloc(256);
         sprintf(tmp, "Size mismatch: 'dots' is %u instead of %u bytes (%u rows X %u modules X 32-bit-int(4 bytes)) long!\0", dots_bytes_length, (flippie->config->num_rows * flippie->config->num_modules * 4), flippie->config->num_rows, flippie->config->num_modules, flippie->config->num_rows, flippie->config->num_modules);
         String s(tmp);
         free(tmp);
         Serial.printf(s.c_str());
         server.send(500, "text/plain", s);
         return false;
      }
      
      unsigned int **int_dots = (unsigned int **)malloc(flippie->config->num_rows * sizeof(unsigned int *));
      unsigned int ptr = 0;
      for (i = 0; i < flippie->config->num_rows; i++) {
         int_dots[i] = (unsigned int *)malloc(flippie->config->num_modules * sizeof(unsigned int));
         for (j = 0; j < flippie->config->num_modules; ++j) {
            int_dots[i][j] = (dots_bytes[ptr]) | (dots_bytes[ptr + 1] << 8) | (dots_bytes[ptr + 2] << 16) | (dots_bytes[ptr + 3] << 24);
            ptr += 4;
         }
      }
      debug_printf("%s", flippie->dots_as_string(int_dots).c_str());

      
      flippie->set_next_and_paint(int_dots, true);

      free(dots_bytes);
      for (i = 0; i < flippie->config->num_rows; i++) {
         free(int_dots[i]);
      }
      free(int_dots);
      server.send(200, "application/json", "true");
   } else if (method == HTTP_GET) {
      debug_printf("%s", flippie->dots_as_string(flippie->get_dots()).c_str());
      unsigned int dots_bytes_length = flippie->config->num_rows * flippie->config->num_modules * 4;
      unsigned char *dots_bytes = (unsigned char *)malloc(dots_bytes_length);
      
      unsigned int dots_string_length =
      flippie->config->num_rows * flippie->config->num_modules * 16 + 3;
      char *dots_string = (char *)malloc(dots_string_length);
      
      unsigned int i, j, pos = 0, k;
      unsigned int **dots = flippie->get_dots();
      for (i = 0; i < flippie->config->num_rows; ++i) {
         for (j = 0; j < flippie->config->num_modules; ++j) {
            k = dots[i][j];
            dots_bytes[pos++] = k & 255;
            dots_bytes[pos++] = (k >> 8) & 255;
            dots_bytes[pos++] = (k >> 16) & 255;
            dots_bytes[pos++] = (k >> 24) & 255;
         }
      }
      b64.encode(dots_bytes, dots_bytes_length, dots_string + 1, &dots_string_length);
      dots_string[0] = '"';
      dots_string[dots_string_length] = '"';
      dots_string[dots_string_length + 1] = '\0';
      server.send(200, "application/json", String(dots_string));
      free(dots_bytes);
      free(dots_string);
   } else {
      return false;
   }
   return true;
}

bool DotsHandler::canHandle(HTTPMethod method, String uri) {
   if (uri == "/dots" && (method == HTTP_GET || method == HTTP_POST)) {
      return true;
   }
   return false;
}
