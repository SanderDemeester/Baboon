#ifndef _GENERAL_
#include "header/general.h"
#endif

#include "header/hex.h"
#include "header/aes.h"

int main(int argc, char *argv[]){
  unsigned char *key;
  unsigned char *input;
  unsigned char *iv;
  
  int key_len;
  int input_len;
  int iv_len;

  if(argc < 5){
    fprintf(stderr, "Usage: %s [-e|-d] <key> <iv> <input>\n", argv[0]);
    return 1;
  }

  key_len = hex_decode(argv[2], &key);
  iv_len = hex_decode(argv[3], &iv);
  input_len = hex_decode(argv[4], &input);
  
  if( !strcmp(argv[1], "-e")){
    unsigned char *ciphertext = (unsigned char*) malloc(input_len); //reverse space
    if(key_len == 16){
      aes_128_encrypt(input, input_len, ciphertext, iv, key);
    }else if(key_len == 32){
      aes_256_encrypt(input, input_len, ciphertext, iv, key);
    }else{
      fprintf(stderr, "Unsupported key length: %d\n",key_len);
      return 2;
    }
    show_hex(ciphertext, input_len);
    free(ciphertext);
  }else if( !strcmp(argv[1], "-d")){
    unsigned char *plaintext = (unsigned char*) malloc(input_len); //reverse space
    if(key_len == 16){
      aes_128_decrypt(input, input_len, plaintext, iv, key);
    }else if(key_len == 32){
      aes_256_decrypt(input, input_len, plaintext, iv, key);
    }else{
      fprintf(stderr, "Unsupported key length: %d\n",key_len);
      return 3;
    }
    show_hex(plaintext, input_len);
    free(plaintext);
  }else{
    fprintf(stderr, "Usage: %s [-e|-d] <key> <iv> <input>\n", argv[0]);
  }

  //free all!!!
  free(iv);
  free(key);
  free(input);
  return 0;
}

