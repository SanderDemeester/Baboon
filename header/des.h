#define _DES_H
#include <assert.h>
//return non-zero
/***********/
/* MACRO'S */
/***********/
#define GET_BIT(array, bit)   (array[(int) (bit / 8)] & (0x80 >> (bit % 8)))
#define SET_BIT(array, bit)   (array[(int) (bit / 8)] |=  (0x80 >> (bit % 8)))
#define CLEAR_BIT(array, bit) (array[(int) (bit / 8)] &= ~(0x80 >> (bit % 8)))

#define DES_BLOCK_SIZE 8 //64 bits, defined in DES standard
#define DES_KEY_SIZE 8 //57 bits used. 64 needed. those 8 bits are used for parity checking (the good old days?), we simply ignore the 8th bits in each byte of our "working block" 
#define PC1_KEY_SIZE 7
#define SUBKEY_SIZE 6
#define EXPANSION_BLOCK_SIZE 6

typedef enum {ENCRYPT,DECRYPT} operation_type;

/*********************************************************************/
/* Overwirtes the target array with the XOR of it and the src array. */
/*********************************************************************/
static void xor(unsigned char *target, const unsigned char *source, int len);


/********************************************************************/
/* Depending on the permute_table, this is the "<3" of our DES code.
 permute table SHOULD have exactly les and les * 8 number of entries.
 copy the second bit of the last byte into the first bit of the first byte of the output.
 the first byte of output comes from the second bits of each input byte.
 the second byte of output comes rom the fouth bits of each input byte
 You see where this is goning..
/********************************************************************/
static void permute(unsigned char target[], const unsigned char src[], const int parmute_table[], int len);

static void rotate_left(unsigned char *target);
static void rotate_right(unsigned char *target);

static void des_block_operate(const unsigned char plaintext[DES_BLOCK_SIZE],
			      unsigned char ciphertext[DES_BLOCK_SIZE],
			      const unsigned char key[DES_KEY_SIZE],
			      operation_type operation);

static void des_operate(const unsigned char *input,
			int input_len,
			unsigned char *output,
			const unsigned *iv, //initialization vector for CBC
			const unsigned *key,
			operation_type operation,
			int trip);

/**************************************************************************************************************/
/* DES-encrypt code.
/* We first figure out how much padding is needed. It will be between one and eight bytes.		      */
/* If the input is already eight-byte aligned, we must add a "dummy" block of eight byte.		      */
/*   we use the byte 0x80 to specify where out padding starts and fill up with zero bytes. 		      */
/* The dummy padding for input with is eight-byte aligned is four when the the plain-text ends with 0x80 byte */
/**************************************************************************************************************/

/***********************/
/* DES-encrypt code.   */
/* key-length: 56-bits */
/***********************/
void des_encrypt(const unsigned char* plaintext,
		 const int plaintext_len,
		 unsigned char *ciphertext,
		 const unsigned char *iv,
		 const unsigned char *key);

/***********************/
/* DES-decrypt code.   */
/* key-length: 56-bits */
/***********************/

void des_decrypt(const unsigned char *ciphertext,
		 unsigned int ciphertext_len,
		 unsigned char *plaintext,
		 const unsigned char *iv,
		 const unsigned char *key);


/*************************/
/* 3DES-encrypt code .   */
/* key-length: 168-bits  */
/*************************/

void des3_encrypt(const unsigned char* plaintext,
		  const int plaintext_len,
		  unsigned char *ciphertext,
		  const unsigned char* iv,
		  const unsigned char *key);

/*************************/
/* 3DES-encrypt code.    */
/* key-length: 168-bits  */
/*************************/

void des3_decrypt(const unsigned char *ciphertext,
		 unsigned int ciphertext_len,
		 unsigned char *plaintext,
		 const unsigned char *iv,
		 const unsigned char *key);
