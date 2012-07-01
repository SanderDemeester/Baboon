#define _AES_H
/**************************/
/* rotate the 4 byte word */
/**************************/
static void rotate_word(unsigned char *w);

/**************************/
/* replace with AES sbox */
/**************************/
static void subsitute_word(unsigned char *w);

/**************************************************/
/* AES key scheduling                             */
/* the key_lengte is in bytes.                    */
/* the number of iterations: ((key_lengte/4)+6)*4 */
/**************************************************/

static void compute_key_schedule(const unsigned char *key,
				 int key_lengte, 
				 unsigned char w[][4]);

/***********************/
/* AES key combination */
/***********************/
static void add_round_key(unsigned char state[][4],
			  unsigned char w[][4]);

/****************************************/
/* subsitute sbox for encryption step1  */
/****************************************/
static void subsitute_bytes(unsigned char state[][4]);

/*****************/
/* AES row shift */
/*****************/
static void shift_rows(unsigned char state[][4]);

/*************************************************/
/* left shift n times, with XOR 0x1B on overflow */
/*************************************************/
unsigned char ntime(unsigned char n);

/******************/
/* AES dotproduct */
/******************/
unsigned char inproduct(unsigned char x, unsigned char y);

/*************************/
/* Columns mixing in AES */
/*************************/
static void mix_columns(unsigned char s[][4]);

/************************/
/* AES Block Encryption */
/************************/
static void aes_block_encrypt(const unsigned char *input_block, 
			      unsigned char *output_block,
			      const unsigned char *key,
			      int key_size);




