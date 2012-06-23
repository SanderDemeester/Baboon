//specification: http://csrc.nist.gov/publications/fips/fips46-3/fips46-3.pdf
//return non-zero
#define GET_BIT (array,bit)   \ (array[(int) (bit / 8)] &   ( 0x80 >> (bit)))
#define SET_BIT (array,bit)   \ (array[(int) (bit / 8)] |=  ( 0x80 >> (bit)))
#define CLEAR_BIT (array,bit) \ (array[(int) (bit / 8)] &= ~( 0x80 >> (bit)))

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

/*********************************************************************/
/* Overwirtes the target array with the XOR of it and the src array. */
/*********************************************************************/

static void xor(unsigned char *target, const unsigned char *source, int len){
  while(len--){
    *target++ ^= *src++;
  }
}

/********************************************************************/
/* Depending on the permute_table, this is the "<3" of our DES code.
/* permute table SHOULD have exactly les and les * 8 number of entries.
/* copy the second bit of the last byte into the first bit of the first byte of the output.
/* the first byte of output comes from the second bits of each input byte.
/* the second byte of output comes rom the fouth bits of each input byte
/* You see where this is goning..
/********************************************************************/
static void permute(unsigned char target[], const unsigned char src[], const int parmute_table[], int len){
  int i;
  for(i = 0; i < len * 8; i++){
    if(GET_BIT(src,(permute_table[i]-1)))
      SET_BIT(target,i);
    else
      CLEAR_BIT(target,i);
  }
}

static void rotate_left(unsigned char* target){
  
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


