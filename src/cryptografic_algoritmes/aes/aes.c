 //specification: csrc.nist.gov/publications/fips/fips197/fips-197.pdf
 #ifndef _AES_H
 #include "header/aes.h"
 #endif

 /***********************/
 /* AES encryption sbox */
 /***********************/
 static unsigned char sbox[16][16] = {
		 {
				 0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,
				 0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76
		 },{
				 0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,
				 0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0
		 },{
				 0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,
				 0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15
		 },{
				 0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,
				 0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75
		 },{
				 0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,
				 0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84
		 },{
				 0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,
				 0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf
		 },{
				 0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,
				 0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8
		 },{
				 0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,
				 0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2
		 },{
				 0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,
				 0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73
		 },{
				 0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,
				 0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb
		 },{
				 0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,
				 0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79
		 },{
				 0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,
				 0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08
		 },{
				 0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,
				 0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a
		 },{
				 0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,
				 0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e
		 },{
				 0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,
				 0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf
		 },{
				 0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,
				 0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
		 },};
 /***********************/
 /* AES inversion sbox  */
 /***********************/
 static unsigned char inversion_sbox[16][16]={
		 {
				 0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,
				 0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb
		 },{
				 0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,
				 0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb
		 },{
				 0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,
				 0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e
		 },{
				 0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,
				 0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25
		 },{
				 0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,
				 0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92
		 },{
				 0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,
				 0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84
		 },{
				 0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,
				 0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06
		 },{
				 0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,
				 0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b
		 },{
				 0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,
				 0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73
		 },{
				 0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,
				 0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e
		 },{
				 0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,
				 0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b
		 },{
				 0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,
				 0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4
		 },{
				 0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,
				 0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f
		 },{
				 0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,
				 0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef
		 },{
				 0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,
				 0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61
		 },{
				 0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,
				 0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
		 },};

/*********************************************************************/
/* Overwirtes the target array with the XOR of it and the src array. */
/*********************************************************************/

static void xor(unsigned char *target, const unsigned char *source, int len){
	while(len--){
		*target++ ^= *source++;
	}
}

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

   int i;
   for(i=0;i < 4; i++){
     /***************************************************************************************************/
     /* we performe the subsitution by using the high-order four bits of each byte as input the the row */
     /*   and the low order four bits as column							       */
     /***************************************************************************************************/
     w[i] = sbox[(w[i] & 0xF0) >> 4][w[i] & 0x0F];
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

/**************************************************/
/* AES key scheduling                             */
/* the key_lengte is in bytes.                    */
/* the number of iterations: ((key_lengte/4)+6)*4 */
/**************************************************/

static void compute_key_schedule(const unsigned char *key,
				 int key_lengte,
				 unsigned char w[][4]){

	int i;
	int key_words = key_lengte >> 2;
	unsigned char round_constant = 0x01;

	//copy key
	memcpy(w,key,key_lengte);

	for(i = key_words; i < 4 * (key_words + 7);i++){
	  memcpy(w[i],w[i-1],4);
	  if(!(i % key_words)){
	    rotate_word(w[i]);

	    subsitute_word(w[i]);

	    if(!( i % 36 )){
		    round_constant = 0x1b;
	    }
	    w[i][0] ^= round_constant;
		  round_constant <<= 1;
	  }else if((key_words > 6) && ((i % key_words) == 4)){
	    subsitute_word(w[i]);
	  }
	  w[i][0] ^= w[i-key_words][0];
	  w[i][1] ^= w[i-key_words][1];
	  w[i][2] ^= w[i-key_words][2];
	  w[i][3] ^= w[i-key_words][3];
	}
}

/***********************/
/* AES Matrix multiply */
/***********************/
static void matrix_multiply(unsigned char matrix1[4][4],
			    unsigned char matrix2[4][4],
			    unsigned char target[4][4]){
  int i;
  int j;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      target[i][j] =
	matrix1[i][0] * matrix2[0][j] +
	matrix1[i][1] * matrix2[1][j] +
	matrix1[i][2] * matrix2[2][j] +
	matrix1[i][3] * matrix2[3][j];
    }
  }
}

/*************************************************/
/* left shift n times, with XOR 0x1B on overflow */
/*************************************************/
unsigned char ntime(unsigned char n){
  return (n << 1) ^ ((n & 0x80) ? 0x1b : 0x00);
}
/*************************/
/* AES dotproduct        */
/* binary multiplication */
/*************************/
unsigned char inproduct(unsigned char x, unsigned char y){
  unsigned char mask;
  unsigned char p = 0;

  for(mask = 0x01; mask; mask <<= 1){
    if(y & mask){
      p ^= x;
    }
    x = ntime(x);
  }
  return p;
}

/*************************/
/* Columns mixing in AES */
/*************************/
static void mix_columns(unsigned char s[][4]){
  int i;
  unsigned char temp[4];

  for(i = 0; i < 4; i++){
    temp[0] = inproduct(2,s[0][i]) ^ inproduct(3,s[1][i]) ^
      s[2][i] ^ s[3][i];

    temp[1] = s[0][i] ^ inproduct(2,s[1][i]) ^
      inproduct(3,s[2][i]) ^ s[3][i];

    temp[2] = s[0][i] ^ s[1][i] ^ inproduct(2,s[2][i]) ^ inproduct(3,s[3][i]);

    temp[3] = inproduct(3,s[0][i]) ^ s[1][i] ^ s[2][i] ^ inproduct(2, s[3][i]);

    s[0][i] = temp[0];
    s[1][i] = temp[1];
    s[2][i] = temp[2];
    s[3][i] = temp[3];
  }
}

/************************/
/* AES Block Encryption */
/************************/
static void aes_block_encrypt(const unsigned char *input_block,
			      unsigned char *output_block,
			      const unsigned char *key,
			      int key_size){
  int i;
  int j;
  int round;
  int number;
  unsigned char state[4][4];
  unsigned char w[60][4];

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      state[i][j] = input_block[i + (4*j)];
    }
  }
  number = (key_size >> 2) + 6;
  compute_key_schedule(key, key_size, w);

  add_round_key(state,&w[0]);

  for(round = 0; round < number; round++){
    subsitute_bytes(state);
    shift_rows(state);
    if(round < (number-1)){
      mix_columns(state);
    }
    add_round_key(state,&w[(round+1)*4]);
  }
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      output_block[i + (4 * j)] = state[i][j];
    }
  }
}

/************************************/
/* START OF AES INVERSION FUNCTIONS */
/************************************/
/********************/
/* Unshift the rows */
/********************/
static void inversion_shift_rows(unsigned char state[][4]){
  int temp;

  temp = state[1][2];
  state[1][2] = state[1][1];
  state[1][1] = state[1][0];
  state[1][0] = state[1][3];
  state[1][3] = temp;

  temp = state[2][0];
  state[2][0] = state[2][2];
  state[2][2] = temp;

  temp = state[2][1];
  state[2][1] = state[2][3];
  state[2][3] = temp;

  temp = state[3][0];
  state[3][0] = state[3][1];
  state[3][1] = state[3][2];
  state[3][2] = state[3][3];
  state[3][3] = temp;
}

/*******************************/
/* Inversion subsitution bytes */
/*******************************/
static void inversion_subsitution_bytes(unsigned char state[][4]){
  int i;
  int j;

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      state[i][j] = inversion_sbox[(state[i][j] & 0xF0) >> 4][state[i][j] & 0x0F];
    }
  }
}

/****************************/
/* Inversion mixing columns */
/****************************/
static void inversion_mix_columns(unsigned char s[][4]){
  int i;
  unsigned char temp[4];

  for(i = 0; i < 4; i++){
    temp[0] = 	inproduct(0x0e, s[0][i]) ^ inproduct(0x0b, s[1][i]) ^
    			inproduct(0x0d, s[2][i]) ^ inproduct(0x09, s[3][i]);
    temp[1] = 	inproduct(0x09, s[0][i]) ^ inproduct(0x0e, s[1][i]) ^
    			inproduct(0x0b, s[2][i]) ^ inproduct(0x0d, s[3][i]);
    temp[2] = 	inproduct(0x0d, s[0][i]) ^ inproduct(0x09, s[1][i]) ^
    			inproduct(0x0e, s[2][i]) ^ inproduct(0x0b, s[3][i]);
    temp[3] = 	inproduct(0x0b, s[0][i]) ^ inproduct(0x0d, s[1][i]) ^
    			inproduct(0x09, s[2][i]) ^ inproduct(0x0e, s[3][i]);

    s[0][i] = temp[0];
    s[1][i] = temp[1];
    s[2][i] = temp[2];
    s[3][i] = temp[3];
  }
}

/************************/
/* AES block decryption */
/************************/
static void aes_block_decrypt(const unsigned char *input_block,
			      unsigned char *output_block,
			      const unsigned char *key,
			      int key_size){

  int i;
  int j;

  int ronde;
  int number;
  unsigned char state[4][4];
  unsigned char w[60][4];

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      state[i][j] = input_block[i+(j*4)];
    }
  }

  number = (key_size >> 2) + 6;
  compute_key_schedule(key,key_size,w);
  add_round_key(state,&w[number*4]);

  for(ronde = number; ronde > 0; ronde--){
    inversion_shift_rows(state);
    inversion_subsitution_bytes(state);
    add_round_key(state,&w[(ronde-1)*4]);
    if(ronde > 1){
      inversion_mix_columns(state);
    }
  }
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      output_block[i+(4*j)] = state[i][j];
    }
  }
}

/******************/
/* AES encryption */
/******************/
static void aes_encrypt(const unsigned char *input,
			int input_len,
			unsigned char *output,
			const unsigned char *iv,
			const unsigned char *key,
			int key_length){
  unsigned char input_block[AES_BLOCK_SIZE];
  
  while(input_len >= AES_BLOCK_SIZE){
    memcpy(input_block, input, AES_BLOCK_SIZE);
    xor(input_block, iv, AES_BLOCK_SIZE); //CBC
    aes_block_encrypt(input_block, output, key,key_length);
    memcpy((void*) iv, (void*) output, AES_BLOCK_SIZE);
    input += AES_BLOCK_SIZE;
    output += AES_BLOCK_SIZE;
    input_len -= AES_BLOCK_SIZE;
  }
}

/******************/
/* AES decryption */
/******************/
static void aes_decrypt(const unsigned char *input,
			int input_len,
			unsigned char *output,
			const unsigned char *iv,
			const unsigned char *key,
			int key_lengte){

  while(input_len >= AES_BLOCK_SIZE){
    aes_block_decrypt(input, output, key ,key_lengte);
    xor(output, iv, AES_BLOCK_SIZE);
    memcpy((void*) iv, (void*) input, AES_BLOCK_SIZE); //CBC
    input += AES_BLOCK_SIZE;
    output += AES_BLOCK_SIZE;
    input_len -= AES_BLOCK_SIZE;
  }
}


/*************************************/
/* AES final 128 encryption function */
/*************************************/
void aes_128_encrypt( const unsigned char *plaintext,
           const int plaintext_len,
           unsigned char ciphertext[],
           void *iv,
           const unsigned char *key){
  //specific key_length;
  aes_encrypt(plaintext, plaintext_len, ciphertext,iv, key, 16);
}
/*************************************/
/* AES final 128 decryption function */
/*************************************/
void aes_128_decrypt( const unsigned char *ciphertext,
           const int ciphertext_len,
           unsigned char plaintext[],
           void *iv,
           const unsigned char *key){
  //specific key_length;
  aes_decrypt(ciphertext, ciphertext_len, plaintext, iv, key, 16);
}

/****************************/
/* AES final 256 encryption */
/****************************/
void aes_256_encrypt( const unsigned char *plaintext,
           const int plaintext_len,
           unsigned char ciphertext[],
           void *iv,
           const unsigned char *key){
  //specific key_length;
  aes_encrypt(plaintext, plaintext_len, ciphertext, iv, key, 32);
}

/*************************************/
/* AES final 256 decryption function */
/*************************************/
void aes_256_decrypt( const unsigned char *ciphertext,
		      const int ciphertext_len,
		      unsigned char plaintext[],
		      void *iv,
		      const unsigned char *key){
  //specific key_length;
  aes_decrypt(ciphertext, ciphertext_len, plaintext, iv, key, 32);
}
