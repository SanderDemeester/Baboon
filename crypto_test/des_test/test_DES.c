#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  unsigned char *key;
  unsigned char *iv;
  unsigned char *input;
  unsigned char *output;
  int key_len;
  int iv_len;
  int output_len;
  int input_len;


  if(argc < 5){
    fprintf(stderr,"Usage: %s [-e|-d] <key> <iv> <input>\n,",argv[0]);
    return 0;
  }
  
  printf("%s \n",argv[4]);
  
  key_len = hex_decode(argv[2],&key);
  iv_len = hex_decode(argv[3],&iv);
  input_len = hex_decode(argv[4],&input);





  output_len = input_len;

  output = (unsigned char*) malloc(output_len+1);
  
  if((!strcmp(argv[1], "-e"))){
    des_encrypt(input, input_len, output, iv, key);
    show_hex(output,output_len);
  }else if(!(strcmp(argv[1],"-d"))){
    des_decrypt(input, input_len, output, iv, key);
    show_hex(output, output_len);
  }else{
    fprintf(stderr,"Usage: %s [-e|-d] <key> <iv> <input>\n",argv[0]);
  }

  free(input);
  free(iv);
  free(key);
  free(output);
  
  return 0;
  
}
