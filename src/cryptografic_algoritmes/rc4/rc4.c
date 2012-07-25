#ifndef _RC4_H
#include "header/rc4.h"
#endif

void rc4_operate(const unsigned char *plaintext,
		 int plaintext_len,
		 unsigned char *cijfertext,
		 unsigned char *key,
		 int key_len,
		 rc4_state *state){
  int i;
  int j;
  unsigned char S[256];
  unsigned char tmp;
  //Key scheduling algoritme
  for(i = 0; i < 256; i++){
    S[i] = i;
  }
  j=0;
  for(i = 0; i < 256; i++){
    j = (j+S[i] + key[i%key_len])%256;
    tmp = S[i];
    S[i] = S[j];
    S[j] = tmp;
  }
  i = 0;
  j = 0;
  while(plaintext_len--){
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    tmp = S[i];
    S[i] = S[j];
    S[j] = tmp;
    *(cijfertext++) = S[(S[i]+S[j]) % 256] ^ *(plaintext++);
  }
}
