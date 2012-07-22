#define _AES_H
#define AES_BLOCK_SIZE 16

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
		     
