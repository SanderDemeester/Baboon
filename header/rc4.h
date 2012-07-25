#define _RC4_H
#define RC4_STATE_ARRAY_LEN 256

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

typedef struct{ 
  int i;
  int j;
  unsigned char S[RC4_STATE_ARRAY_LEN];
}rc4_state;

void rc4_operate(const unsigned char *plaintext,
		 int plaintext_len,
		 unsigned char *cijfertext,
		 unsigned char *key,
		 int key_len,
		 rc4_state *state);

/************************************/
/* RC4 key-length wrapper functions */
/************************************/
void rc4_40_encrypt( const unsigned char *plaintext,
		     const int plaintext_len,
		     unsigned char ciphertext[],
		     void *state,
		     const unsigned char *key);

void rc4_40_decrypt( const unsigned char *ciphertext,
		     const int ciphertext_len,
		     unsigned char plaintext[],
		     void *state,
		     const unsigned char *key);

void rc4_128_encrypt( const unsigned char *plaintext, 
		      const int plaintext_len,
		      unsigned char ciphertext[],
		      void *state,
		      const unsigned char *key);

void rc4_128_decrypt( const unsigned char *ciphertext,
		      const int ciphertext_len,
		      unsigned char plaintext[],
		      void *state,
		      const unsigned char *key);
		    
