#ifndef BASE64_H
#define BASE64_H

#define WHITESPACE 64
#define EQUALS     65
#define INVALID    66

class Base64 {
public:
   int encode(const void* data_buf, unsigned int dataLength, char* result, unsigned int *resultSize);
   int decode(char *in, unsigned int inLen, unsigned char *out, unsigned int *outLen);
private:
   static const char* base64chars;
   static const unsigned char d[256];
};

#endif
