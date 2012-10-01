#ifndef _USERMODE_CRYPTO_MANAGEMENT
#include "header/usermod_cryptomanagement.h"
#endif
#ifndef _GENERAL
#include "header/general.h"
#endif

void usermode_aes(int argc, char** argv){
  int offset_to_arguments = 4; //offset for arguments
  
  unsigned char *key = NULL;
  unsigned char *input = NULL;
  unsigned char *iv = NULL; 
  
}
void usermode_rc4(int argc, char** argv){
  printf("rc4 \n");
}
void usermode_des(int argc, char** argv){
    printf("des \n");
}
void usermode_3des(int argc, char** argv){
  printf("3des \n");
}
void usermode_list_blockcipher(int argc, char** argv){
  printf("%s \n", "CRYPTO USERMODE LIST BLOCK CIPHERS");
}
void usermode_list_streamcipher(int argc, char** argv){
  printf("%s \n", "CRYPTO USERMODE LIST STREAM CIPHERS");
}
void usermode_crypto_help(int argc, char** argv){
  printf("%s \n", "USERMOD CRYPTO HELP SECTION");
  printf("Crypto flag options\n");
  printf("--crypto [--block-cipher]|[--stream-cipher]:\t\t use block-cipher protocols or stream-cipher protocols\n");
  printf("--block-cipher  [--list]: \t\t\t\t list all available block ciphers in this section of crypto-ciphers\n");
  printf("--stream-cipher [--list]: \t\t\t\t list all avaiabale stream ciphers in this section of crypto-ciphers\n");
  exit(0);
}
