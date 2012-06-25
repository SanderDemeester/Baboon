//specification: http://csrc.nist.gov/publications/fips/fips46-3/fips46-3.pdf
#ifndef _DES_H
#include "header/des.h"
#endif

#ifndef _GENERAL_
#include "header/general.h"
#endif

/********************************/
/* DES inital permutation table */
/* transpose the input block    */
/* move bit 58 to pos1,         */
/* move bit 50 to pos2 etc      */
/********************************/

static const int ip_table[] = {
  58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6,
  64, 56, 48, 40, 32, 24, 16, 8,
  57, 49, 41, 33, 25, 17, 9,  1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61 ,53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7
};

/*******************************/
/* Final DES permutation table */
/* this inverts the ip_table   */
/*******************************/
static const int fp_table[] = {
  40, 8, 48, 16, 56, 24, 64, 32,
  39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30,
  37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28,
  35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26,
  33, 1, 41, 9, 49,  17, 57, 25
};

/*********************************************************************/
/* Key transformation table.					     */
/* 64-bit key to 56-bit key, this table describe this transformation */
/*********************************************************************/
static const int permutation_table_1[] = {
  57, 49, 41, 33, 25, 17, 9,  1,
  58, 50, 42, 34, 26, 18, 10, 2,
  59, 51, 43, 35, 27, 19, 11, 3,
  60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15, 7,
  62, 54, 46, 38, 30, 22, 14, 6,
  61, 53, 45, 37, 29, 21, 13, 5,
  28, 20, 12, 4
};

/*************************************************************************/
/* Compression permutation table.					 */
/* Provides a subset of 48 bits.					 */
/* exmpl: bit in pos 33 of the shifted key moves to pos 35 of the output */
/*************************************************************************/
static const int permutation_table_2[] = {
  14, 17, 11, 24, 1, 5, 3, 28,
  15, 6, 21, 10, 23, 19, 12, 4,
  26, 8, 16, 7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55, 30, 40,
  51, 45, 33, 48, 44, 49, 39, 56,
  34, 53, 46, 42, 50, 36, 29, 32,
};

/********************************************************************/
/* Expantions table.						    */
/* shows wich output positions corresponds to with input position.  */
/********************************************************************/
static const int expansion_table[] = {
  32, 1, 2, 3, 4, 5,
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
  16, 7, 20, 21,
  29, 12, 28, 17,
  1, 15, 23, 26,
  5, 18, 31, 10,
  2, 8, 24, 14,
  32, 27, 3, 9,
  19, 13, 30, 6,
  22, 11, 4, 25
};

/***************************/
/* Lookup table for sboxes */
/* the magic sboxes        */
/***************************/

static const int sbox[8][64] = {
{ 
  14,0,4,15,13,7,1,4,2,14,15,2,11,13,8,1,
  3,10,10,6,6,12,12,11,5,9,9,5,0,3,7,8,
  4,15,1,12,14,8,8,2,13,4,6,9,2,1,11,7,
  15,5,12,11,9,3,7,14,3,10,10,0,5,6,0,13
},{
  15,3,1,13,8,4,14,7,6,15,11,2,3,8,4,14,
  9,12,7,0,2,1,13,10,12,6,0,9,5,11,10,5,
  0,13,14,8,7,10,11,1,10,3,4,15,13,4,1,2,
  5,11,8,6,12,7,6,12,9,0,3,5,2,14,15,9
},{
  10,13,0,7,9,0,14,9,6,3,3,4,15,6,5,10,
  1,2,13,8,12,5,7,14,11,12,4,11,2,15,8,1,
  13,1,6,10,4,13,9,0,8,6,15,9,3,8,0,7,
  11,4,1,15,2,14,12,3,5,11,10,5,14,2,7,12
},{
  7,13,13,8,14,11,3,5,0,6,6,15,9,0,10,3,
  1,4,2,7,8,2,5,12,11,1,12,10,4,14,15,9,
  10,3,6,15,9,0,0,6,12,10,11,1,7,13,13,8,
  15,9,1,4,3,5,14,11,5,12,2,7,8,2,4,14
},{
  2,14,12,11,4,2,1,12,7,4,10,7,11,13,6,1,
  8,5,5,0,3,15,15,10,13,3,0,9,14,8,9,6,
  4,11,2,8,1,12,11,7,10,1,13,14,7,2,8,13,
  15,6,9,15,12,0,5,9,6,10,3,4,0,5,14,3
},{
  12,10,1,15,10,4,15,2,9,7,2,12,6,9,8,5,
  0,6,13,1,3,13,4,14,14,0,7,11,5,3,11,8,
  9,4,14,3,15,2,5,12,2,9,8,5,12,15,3,10,
  7,11,0,14,4,1,10,7,1,6,13,0,11,8,6,13
},{
  4,13,11,0,2,11,14,7,15,4,0,9,8,1,13,10,
  3,14,12,3,9,5,7,12,5,2,10,15,6,8,1,6,
  1,6,4,11,11,13,13,8,12,1,3,4,7,10,14,7,
  10,9,15,5,6,0,8,15,0,14,5,2,9,3,2,12
},{
  13,1,2,15,8,13,4,8,6,10,15,3,11,7,1,4,
  10,12,9,5,3,6,14,11,5,0,0,14,12,9,7,2,
  7,2,11,1,4,14,1,7,9,4,12,10,14,8,2,13,
  0,15,6,12,10,9,13,0,15,3,3,5,5,6,8,11
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
  target[2] = (target[2] << 1) | ((target[3] & 0x80) >> 7);

  /* special handling for byte 3 */
  carry_right = (target[3] & 0x08) >> 3;
  
  target[3] = (((target[3] << 1) | ((target[4] & 0x80 ) >> 7)) & ~0x10) | carry_left;
  
  /* and the rest */
  
  target[4] = (target[4] << 1) | ((target[5] & 0x80) >> 7);
  target[5] = (target[5] << 1) | ((target[6] & 0x80) >> 7);
  target[6] = (target[6] << 1) | carry_right;
}

static void rotate_right(unsigned char *target){

 //while performing the rotate functions, we need to record a carry
  int carry_left = 0;
  int carry_right = 0;

  carry_right = (target[6] & 0x01) << 3;
  
  target[6] = (target[6] >> 1) | ((target[5] & 0x01) << 7);
  target[5] = (target[5] >> 1) | ((target[4] & 0x01) << 7);
  target[4] = (target[4] >> 1) | ((target[3] & 0x01) << 7);

  carry_left = (target[3] & 0x10) << 3;
  
  target[3] = (((target[3] >> 1) | ((target[2] & 0x01) << 7)) & ~0x80) | carry_right;

  target[2] = (target[2] >> 1) | ((target[1] & 0x01) << 7);
  target[1] = (target[1] >> 1) | ((target[0] & 0x01) << 7);
  target[0] = (target[0] >> 1) | carry_left;
}

static void des_block_operate(const unsigned char plaintext[DES_BLOCK_SIZE],
			      unsigned char ciphertext[DES_BLOCK_SIZE],
			      const unsigned char key[DES_KEY_SIZE],
			      operation_type operation){
  //holding area's, out working stream goes through all of them
  unsigned char ip_block[DES_BLOCK_SIZE];
  unsigned char expansion_block[EXPANSION_BLOCK_SIZE];
  unsigned char subsitation_block[DES_BLOCK_SIZE/2];
  unsigned char permutation_box_target[DES_BLOCK_SIZE/2];
  unsigned char recomb_box[DES_BLOCK_SIZE/2];

  unsigned char pc1key[PC1_KEY_SIZE];
  unsigned char subkey[SUBKEY_SIZE];

  int ronde;
 
  /****************************************************/
  /* LADY'S AND GENT, START YOUR PERMUTATION ENGINE!! */
  /****************************************************/
  
  permute(ip_block,plaintext, ip_table, DES_BLOCK_SIZE);

  permute(pc1key, key, permutation_table_1,PC1_KEY_SIZE);
  for(ronde = 0; ronde < 16; ronde++){
    /* feitel function on the first half of the block in 'ip_block */
    /* "expansion" (32 bits of ip_block); 16 of those are repeated */
    permute(expansion_block, ip_block+4, expansion_table, 6); //4 bytes

    /* Key mixing */
    /* rotation over both halfes of the inital key */
    if(operation == ENCRYPT){
      rotate_left(pc1key);
      //rotate 2 times.
      if(!(ronde <= 1 || ronde == 8 || ronde == 15)){
	rotate_left(pc1key);
	#ifdef _DEBUG
	printf("%.02x \n",pc1key);
	#endif
      }
    }

    permute(subkey,pc1key,permutation_table_2,SUBKEY_SIZE);
    
    if(operation == DECRYPT){
      rotate_right(pc1key);
      if(!(ronde >= 14 || ronde == 7 || ronde == 0)){
	//rotate 2 times
	rotate_right(pc1key);
      }
    }

    xor(expansion_block, subkey, 6);
    
    //subsitution: from updated expantion block to ciphertext block
    memset((void*) subsitation_block, 0, DES_BLOCK_SIZE / 2); //we already have memory, no need for calloc.
    subsitation_block[0] =  sbox[0][(expansion_block[0] & 0xFC) >> 2] << 4;
    subsitation_block[0] |= sbox[1][(expansion_block[0] & 0x03) << 4 | (expansion_block[1] & 0xF0) >> 4];

    subsitation_block[1] =  sbox[2][(expansion_block[1] & 0x0F) << 2 | (expansion_block[2] & 0xC0) >> 6 ] << 4;
    subsitation_block[1] |= sbox[3][(expansion_block[2] & 0x3F)];

    subsitation_block[2] =  sbox[4][(expansion_block[3] & 0xFC) >> 2] << 4;
    subsitation_block[2] |= sbox[5][(expansion_block[3] & 0x03) << 4 | (expansion_block[4] & 0xF0) >> 4];

    subsitation_block[3] =  sbox[6][(expansion_block[4] & 0x0F) << 2 | (expansion_block[5] & 0xC0) >> 6] << 4;
    subsitation_block[3] |= sbox[7][(expansion_block[5] & 0x3F)];

    //permutate
    permute(permutation_box_target, subsitation_block, p_table, DES_BLOCK_SIZE / 2);
    
    //recombine
    memcpy((void *) recomb_box, (void *) ip_block,DES_BLOCK_SIZE / 2);
    memcpy((void *) ip_block,   (void *) (ip_block + 4),DES_BLOCK_SIZE / 2);
    
    xor(recomb_box, permutation_box_target,DES_BLOCK_SIZE / 2);
    memcpy((void *) (ip_block + 4),(void *) recomb_box, DES_BLOCK_SIZE / 2);
  }
  //on more time.
  memcpy((void*) recomb_box,   (void*) ip_block ,DES_BLOCK_SIZE / 2 );
  memcpy((void*) ip_block,     (void*) (ip_block+4),DES_BLOCK_SIZE / 2);
  memcpy((void*) (ip_block+4), (void*) recomb_box,DES_BLOCK_SIZE / 2);
  
  //final permutation
  permute(ciphertext, ip_block, fp_table, DES_BLOCK_SIZE);

}


static void des_operate(const unsigned char *input,
			int input_len,
			unsigned char *output,
			const unsigned *iv,
			const unsigned *key,
			operation_type operation,
			int trip){

  unsigned char input_block[DES_BLOCK_SIZE];
  
  //make assertation that the input_len is div by the blocksize
  assert(!(input_len % DES_BLOCK_SIZE));

  while(input_len){
    memcpy( (void*) input_block, (void*) input, DES_BLOCK_SIZE);

    if(operation == ENCRYPT){
      xor(input_block, iv, DES_BLOCK_SIZE); //CBC
      des_block_operate(input_block, output ,key, operation);
  
      if(trip){
	
	memcpy(input_block, output, DES_BLOCK_SIZE);
	des_block_operate(input_block,output, key + DES_KEY_SIZE,
			  DECRYPT);
	memcpy(input_block,output,DES_BLOCK_SIZE);
	des_block_operate(input_block, output, key + (DES_KEY_SIZE*2),
			  operation);

      }
      memcpy( (void*) iv, (void*) output, DES_BLOCK_SIZE); //CBC

    }

    if(operation == DECRYPT){

      if(trip){
	des_block_operate(input_block, output, key + (DES_KEY_SIZE*2), 
			  operation);
	memcpy(input_block, output, DES_BLOCK_SIZE);
	des_block_operate(input_block, output, key + DES_KEY_SIZE, 
			  ENCRYPT);
	memcpy(input_block, output, DES_BLOCK_SIZE);
	des_block_operate(input_block, output, key, operation);

      }else{

	des_block_operate(input_block, output, key, operation);

      }

      xor(output, iv, DES_BLOCK_SIZE);
      memcpy( (void*) iv, (void*) input, DES_BLOCK_SIZE); //CBC

    }

    input += DES_BLOCK_SIZE;
    output += DES_BLOCK_SIZE;
    input_len -= DES_BLOCK_SIZE;
  }
}

void des_encrypt(const unsigned char* plaintext,
		 const int plaintext_len,
		 unsigned char *ciphertext,
		 const unsigned char *iv,
		 const unsigned char *key){
  
  unsigned char *padded_plaintext;
  int padding_len;
  
  //Padding length.
  padding_len = DES_BLOCK_SIZE - (plaintext_len % DES_BLOCK_SIZE);

  padded_plaintext = (char*)  malloc(plaintext_len + padding_len);

  //implementation of NIST 800-3A padding (what you can learn from reading the spec)
  memset(padded_plaintext, padding_len, plaintext_len + padding_len);
  
  /* this is our "anker" so we know were out padding begins */
  /* padded_plaintext[plaintext_len] = 0x80; */

  memcpy(padded_plaintext,plaintext,plaintext_len);
  
  des_operate(plaintext, plaintext_len, ciphertext, iv, key, ENCRYPT,0);
  free(padded_plaintext);
}


void des_decrypt(const unsigned char *ciphertext,
		 unsigned int ciphertext_len,
		 unsigned char *plaintext,
		 const unsigned char *iv,
		 const unsigned char *key){

  des_operate(ciphertext, ciphertext_len, plaintext, iv, key, DECRYPT,0);
  /* plaintext[ciphertext_len-plaintext[ciphertext_len-1]] = 0x0; //NULL byte */

}

void des3_encrypt(const unsigned char* plaintext,
		 const int plaintext_len,
		 unsigned char *ciphertext,
		 const unsigned char *iv,
		 const unsigned char *key){
  
  unsigned char *padded_plaintext;
  int padding_len;
  
  //Padding length.
  padding_len = DES_BLOCK_SIZE - (plaintext_len % DES_BLOCK_SIZE);

  padded_plaintext = (char*)  malloc(plaintext_len + padding_len);

  //implementation of NIST 800-3A padding (what you can learn from reading the spec)
  memset(padded_plaintext, padding_len, plaintext_len + padding_len);
  
  /* this is our "anker" so we know were out padding begins */
  /* padded_plaintext[plaintext_len] = 0x80; */

  memcpy(padded_plaintext,plaintext,plaintext_len);
  
  /* the "1" is to enable 3des -> 168bit key */
  /* des_operate(padded_plaintext, plaintext_len + padding_len, ciphertext, iv, key, ENCRYPT, 1); */
  des_operate(plaintext, plaintext_len, ciphertext, iv, key, ENCRYPT,1);
  free(padded_plaintext);
}


void des3_decrypt(const unsigned char *ciphertext,
		 unsigned int ciphertext_len,
		 unsigned char *plaintext,
		 const unsigned char *iv,
		  const unsigned char *key){

  des_operate(ciphertext, ciphertext_len, plaintext, iv, key, DECRYPT, 1);

  /* plaintext[ciphertext_len-plaintext[ciphertext_len-1]] = 0x0; //NULL byte */
}
