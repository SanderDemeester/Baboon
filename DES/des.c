//specification: http://csrc.nist.gov/publications/fips/fips46-3/fips46-3.pdf
#ifndef _DES_H
#include "header/des.h"
#endif

/********************************/
/* DES inital permutation table */
/********************************/

static const int ip_table[] = {
  58,50,42,34,26,18,10,2,
  60,52,44,36,26,20,12,4,
  62,54,46,38,30,22,14,6,
  64,56,48,40,32,24,16,8,
  57,49,41,33,25,17,9,1,
  59,51,43,35,27,19,11,3,
  61,53,45,37,29,21,13,5,
  63,55,47,39,31,23,25,7};

/*****************************/
/* this inverts the ip_table */
/*****************************/
static const int fp_table[] = {
  40,8,48,16,56,24,64,32,
  39,7,47,15,55,23,63,31,
  38,6,46,14,54,22,62,30,
  37,5,45,13,53,21,61,29,
  36,4,44,12,52,20,60,28,
  35,3,43,11,51,19,59,27,
  34,2,42,10,50,18,58,26,
  33,1,41,9,49,17,57,25
};

/***********************************************************************************/
/* This table is for the left half of the key as wel for the right half of the key */
/***********************************************************************************/
static const int permutation_table_1[] = {
  57,49,41, 33, 25, 17, 9,
  1, 58, 50, 42, 34, 26, 18,
  10, 2, 59, 51, 43, 35, 27,
  19, 11, 3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15,
  7, 62, 54, 46, 38, 30, 22,
  14, 6, 61, 53, 45, 37, 29,
  21, 13, 5, 28, 20, 12, 4,
};

static const int permutation_table_2[] = {
  14, 17, 11, 24, 1, 5, 3, 28,
  15, 6, 21, 10, 23, 19, 12, 4,
  26, 8, 16, 7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55, 30, 40,
  51, 45, 33, 48, 44, 49, 39, 56,
  34, 53, 46, 42, 50, 36, 29, 32,
};

static const int expansion_table[] = {
  32,1, 2, 3, 4, 5,
  4, 5, 6, 7, 8, 9,
  8, 9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1,
};

/*********************************/
/* final input block permutation */
/*********************************/
static const int p_table[] = {
  16,7,20,21,
  29,12,28,17,
  1,15,23,26,
  5,18,31,10,
  2,8,24,14,
  32,27,3,9,
  19,13,30,6,
  22,11,4,25
};

/***************************/
/* Lookup table for sboxes */
/***************************/

static const int sbox[8][64] = {
{ 
  14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
  0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
  4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
  15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},{
  15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
  3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
  0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
  13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},{
  10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
  13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
  13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
  1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},{
  7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
  13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
  10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
  3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},{
  2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
  14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
  4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
  11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},{
  12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
  10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
  9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
  4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},{
  4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
  13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
  1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
  6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},{
  13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
  1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
  7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
  2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
}};

  
/*********************************************************************/
/* Overwirtes the target array with the XOR of it and the src array. */
/*********************************************************************/

static void xor(unsigned char *target, const unsigned char *source, int len){
  while(len--){
    *target++ ^= *source++;
  }
}

/********************************************************************/
/* Depending on the permute_table, this is the "<3" of our DES code.
 permute table SHOULD have exactly les and les * 8 number of entries.
 copy the second bit of the last byte into the first bit of the first byte of the output.
 the first byte of output comes from the second bits of each input byte.
 the second byte of output comes rom the fouth bits of each input byte
 You see where this is goning..
/********************************************************************/
static void permute(unsigned char target[], const unsigned char src[], const int permute_table[], int len){
  int i;
  for(i = 0; i < len * 8; i++){
    if(GET_BIT(src,(permute_table[i]-1)))
      SET_BIT(target,i);
    else
      CLEAR_BIT(target,i);
  }
}

static void rotate_left(unsigned char *target){
  
  //while performing the rotate functions, we need to record a carry
  int carry_left = 0;
  int carry_right = 0;
  
  carry_left = (target[0] & 0x80) >> 3; //calculate carry bit
  
  
  /* each byte of the key, a 7 byte array is left-shifted by one splace, and the MSB of the next byte is used as the LSB */
  
  target[0] = (target[0] << 1) | ((target[1] & 0x80) >> 7);
  target[1] = (target[1] << 1) | ((target[2] & 0x80) >> 7);
  target[0] = (target[0] << 1) | ((target[1] & 0x80) >> 7);

  /* special handling for byte 3 */
  carry_right = (target[3] & 0x80) >> 3;
  
  target[3] = (((target[3] << 1) | ((target[4] & 0x08 ) >> 7)) & ~0x10) | carry_left;
  
  /* and the rest */
  
  target[4] = (target[4] << 1) | ((target[5] & 0x80) >> 7);
  target[5] = (target[5] << 1) | ((target[6] & 0x80) >> 7);
  target[6] = (target[6] << 1) | carry_right;
}


