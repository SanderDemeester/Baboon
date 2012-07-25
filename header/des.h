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
/* HEADER FILE CRYPTO FUNCTIONS SIGNATURE LAYOUT		     */
/* All cryptografic functions SHOULD have the same layout structuren */
/* 								     */
/*   first arugment,  type: const unsigned char			     */
/*   second argument, type: const int				     */
/*   third argument,  type: unsigned char			     */
/*   fourth argument, type: void *				     */
/*   fifth argument,  type: const unsigned char			     */
/*********************************************************************/

/***********************/
/* DES-encrypt code.   */
/* key-length: 56-bits */
/***********************/
void des_encrypt( const unsigned char *plaintext,
		  const int plaintext_len,
		  unsigned char *ciphertext,
		  void *iv,
		  const unsigned char *key);

/***********************/
/* DES-decrypt code.   */
/* key-length: 56-bits */
/***********************/

void des_decrypt( const unsigned char *ciphertext,
		  const int ciphertext_len,
		  unsigned char *plaintext,
		  void *iv,
		  const unsigned char *key);


/*************************/
/* 3DES-encrypt code .   */
/* key-length: 168-bits  */
/*************************/

void des3_encrypt( const unsigned char *plaintext,
		   const int plaintext_len,
		   unsigned char *ciphertext,
		   void *iv,
		   const unsigned char *key);

/*************************/
/* 3DES-decrypt code.    */
/* key-length: 168-bits  */
/*************************/

void des3_decrypt( const unsigned char *ciphertext,
		   const int ciphertext_len,
		   unsigned char *plaintext,
		   void *iv,
		   const unsigned char *key);
