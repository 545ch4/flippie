#include "base64.h"

int Base64::encode(unsigned char* in, unsigned int length, char* out) {
   char buff1[3];
   char buff2[4];
   unsigned int i = 0, j, in_pos = 0, out_pos = 0;
   for(in_pos = 0; in_pos < length; i++) {
      buff1[i++] = in[in_pos];
      if (i==3) {
         out[out_pos++] = encodeCharacterTable[(buff1[0] & 0xfc) >> 2];
         out[out_pos++] = encodeCharacterTable[((buff1[0] & 0x03) << 4) + ((buff1[1] & 0xf0) >> 4)];
         out[out_pos++] = encodeCharacterTable[((buff1[1] & 0x0f) << 2) + ((buff1[2] & 0xc0) >> 6)];
         out[out_pos++] = encodeCharacterTable[buff1[2] & 0x3f];
         i = 0;
      }
      
      if (--i) {
         for(j=i;j<3;j++) buff1[j] = '\0';
         
         buff2[0] = (buff1[0] & 0xfc) >> 2;
         buff2[1] = ((buff1[0] & 0x03) << 4) + ((buff1[1] & 0xf0) >> 4);
         buff2[2] = ((buff1[1] & 0x0f) << 2) + ((buff1[2] & 0xc0) >> 6);
         buff2[3] = buff1[2] & 0x3f;
         
         for (j = 0; j < (i + 1); j++) {
            out[out_pos++] = encodeCharacterTable[buff2[j]];
         }
         
         while(i++ < 3){
            out[out_pos++] = '=';
         }
      }
      
   }
   out[out_pos++] = '\0';
   return out_pos;
}
   
int Base64::decode(char* in, unsigned int length, unsigned char* out) {
   unsigned char buff1[4];
   unsigned char buff2[4];
   unsigned int i = 0, j, in_pos = 0, out_pos = 0;
   
   for(in_pos = 0; in_pos < length; i++) {
      buff2[i] = in[in_pos];
      if(buff2[i] != '=') {
         if (++i == 4) {
            for (i = 0; i != 4; i++) {
               buff2[i] = decodeCharacterTable[buff2[i]];
            }
            
            out[out_pos++] = (unsigned char)((buff2[0] << 2) + ((buff2[1] & 0x30) >> 4));
            out[out_pos++] = (unsigned char)(((buff2[1] & 0xf) << 4) + ((buff2[2] & 0x3c) >> 2));
            out[out_pos++] = (unsigned char)(((buff2[2] & 0x3) << 6) + buff2[3]);
            
            i = 0;
         }
      } else {
         break;
      }
   }
   
   if(i > 0) {
      for(j = i; j < 4; j++) {
         buff2[j] = '\0';
      }
      for(j = 0; j < 4; j++) {
         buff2[j] = decodeCharacterTable[buff2[j]];
      }
      
      buff1[0] = (buff2[0] << 2) + ((buff2[1] & 0x30) >> 4);
      buff1[1] = ((buff2[1] & 0xf) << 4) + ((buff2[2] & 0x3c) >> 2);
      buff1[2] = ((buff2[2] & 0x3) << 6) + buff2[3];
      
      for (j = 0; j < (i - 1); j++) {
         out[out_pos++] = (unsigned char)buff1[j];
      }
   }
   out[out_pos++] = '\0';
   return out_pos;
}
