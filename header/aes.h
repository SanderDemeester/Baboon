#define _AES_H
#define AES_BLOCK_SIZE 16

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

/*************************************/
/* AES final 128 encryption function */
/*************************************/
void aes_128_encrypt( const unsigned char *plaintext,
		      const int plaintext_len,
		      unsigned char ciphertext[],
		      void *iv,
		      const unsigned char *key);
/*************************************/
/* AES final 128 decryption function */
/*************************************/
void aes_128_decrypt( const unsigned char *ciphertext,
		      const int ciphertext_len,
		      unsigned char plaintext[],
		      void *iv,
		      const unsigned char *key);

/****************************/
/* AES final 256 encryption */
/****************************/
void aes_256_encrypt( const unsigned char *plaintext,
		      const int plaintext_len,
		      unsigned char ciphertext[],
		      void *iv,
		      const unsigned char *key);

/*************************************/
/* AES final 256 decryption function */
/*************************************/
void aes_256_decrypt( const unsigned char *ciphertext,
		      const int ciphertext_len,
		      unsigned char plaintext[],
		      void *iv,
		      const unsigned char *key);
		     
