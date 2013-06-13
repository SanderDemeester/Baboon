#ifndef _HUGE_G
#include "header/huge.h"
#endif

#ifndef _RSA_
#include "header/rsa.h"
#endif

#ifndef _GENERAL
#include "header/general.h"
#endif
int rsa_encrypt(unsigned char*message,
		unsigned int len,
		unsigned char **ciphertext,
		rsa_key *public_key){
  int i;
  huge c;
  huge m;
  int modulus_length;
  int block_size;
  unsigned char*padding_block = (unsigned char*) malloc(modulus_length);
  int encrypted_size = 0;
  
  *ciphertext = NULL;
  
  while(len){
    encrypted_size += modulus_length;
    // PKCS 1.5 11 bytes header
    block_size = (len < modulus_length - 11) ? len : (modulus_length - 11);
    memset(padding_block, 0, modulus_length);
    memset(padding_block + (modulus_length - block_size),
	   message, block_size);

    padding_block[1] = 0x02;
    
    for(i = 2; i < (modulus_length - block_size - 1); i++){
      padding_block[i] = i;
    }
      
    load_huge(&m, padding_block, modulus_length);
    mod_pow(&m, public_key->exp,public_key->mod, &c);
    
    *ciphertext = (unsigned char*) realloc(*ciphertext, encrypted_size);
    unload_huge(&c,*ciphertext + (encrypted_size - modulus_length),
		modulus_length);
    
    len -= block_size;
    message += block_size;
    free_huge(&m);
    free_huge(&c);
  }
  free(padding_block);
  return encrypted_size;
  
}
