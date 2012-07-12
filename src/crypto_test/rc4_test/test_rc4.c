#ifndef _GENERAL_
#include "header/general.h"
#endif

#include "header/rc4.h"
#include "header/hex.h"

int main(int argc, char *argv[]){
  unsigned char *key;
  unsigned char *input;
  unsigned char *output;
  int key_len;
  int input_len;
  
  if(argc < 4){
    fprintf(stderr, "Gebruik: %s [-e|-d] <key> <input>\n",argv[0]);
    exit(0);
  }
  key_len = hex_decode(argv[2],&key);
  input_len = hex_decode(argv[3],&input);
  
  output = malloc(input_len);
  rc4_operate(input,input_len,output,key,key_len);
  printf("Resultaat: ");
  show_hex(output, input_len);
  
  free(key);
  free(input);

  return 0;
}
