#ifndef BASE64_H
#define BASE64_H
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66

class Base64 {
public:
   int encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);
   int decode(char *in, size_t inLen, unsigned char *out, size_t *outLen);
   static char base64chars[65];
   static unsigned char d[256];
};

#endif
