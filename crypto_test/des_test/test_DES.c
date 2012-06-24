#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  unsigned char *key;
  unsigned char *iv;
  unsigned char *input;
  unsigned char *output;
  int output_len;
  int input_len;


  if(argc < 4){
    fprintf(stderr,"Usage: %s <key> <iv> <input>\n,",argv[0]);
    return 0;
  }

  key = argv[1];
  iv = argv[2];
  input = argv[3];

  output_len = strlen(input);
  input_len = output_len;
  
  output = (unsigned char*) malloc(output_len+1);
  des_encrypt(input,input_len, output, iv, key);
  
  while(output_len--){
    printf("%.02x", *output++);
  }
  printf("\n");
  return 0;
}
