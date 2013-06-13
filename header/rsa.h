#define _RSA_

typedef struct{
  huge *mod;
  huge *exp;
}rsa_key;


int rsa_encrypt(unsigned char*message,
		unsigned int len,
		unsigned char **ciphertext,
		rsa_key *public_key);

  
