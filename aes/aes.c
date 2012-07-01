//specification: csrc.nist.gov/publications/fips/fips197/fips-197.pdf
#ifndef _AES_H
#include "header/aes.h"
#endif

/***********************/
/* AES encryption sbox */
/***********************/

/***********************************/
/* AES rotation of the 4 byte word */
/***********************************/

static void rotate_word(unsigned char *w){
  unsigned char temp;
  temp = w[0];
  w[0] = w[1];
  w[1] = w[2];
  w[2] = w[3];
  w[3] = temp;
}
