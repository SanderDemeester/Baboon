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

/**************************/
/* replace with AES sbox */
/**************************/
static void subsitute_word(unsigned char *w){
  
  int i = 0;
  for(;i < 4; i++){
    /***************************************************************************************************/
    /* we performe the subsitution by using the high-order four bits of each byte as input the the row */
    /*   and the low order four bits as column							       */
    /***************************************************************************************************/
    w[i] = sbox[(w[i] & 0xF0) << 4][w[i] & 0x0F]; 
      }
  }



/***********************/
/* AES key combination */
/***********************/
static void add_round_key(unsigned char state[][4],
			  unsigned char w[][4]){

  int i;
  int j;

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      state[j][i] = state[j][i] ^ w[i][j];
    }
  }
}

/****************************************/
/* subsitute sbox for encryption step1  */
/****************************************/
static void subsitute_bytes(unsigned char state[][4]){
  
  int i;
  int j;
  
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      state[i][j] = sbox[(state[i][j] & 0xF0) >> 4][state[i][j] & 0x0F];
    }
  }
}


/*****************/
/* AES row shift */
/*****************/
static void shift_rows(unsigned char state[][4]){
  
  int temp;
  temp = state[1][0];

  state[1][0] = state[1][1];
  state[1][1] = state[1][2];
  state[1][2] = state[1][3];
  state[1][3] = temp;

  temp = state[2][0];
  state[2][0] = state[2][2];
  state[2][2] = temp;

  temp = state[2][1];
  state[2][1] = state[2][3];
  state[2][3] = temp;

  temp=state[3][3];
  state[3][3] = state[3][2];
  state[3][2] = state[3][1];
  state[3][1] = state[3][0];
  state[3][0] = temp;
}
