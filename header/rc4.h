#define _RC4_H
#define RC4_STATE_ARRAY_LEN 256

void rc4_operate(const unsigned char *plaintext,
		 int plaintext_len,
		 unsigned char *cijfertext,
		 unsigned char *key,
		 int key_len,
		 rc4_state *state);

typedef struct { 
  int i;
  int j;
  unsigned char S[RC4_STATE_ARRAY_LEN];
}rc4_state;
