#ifndef _USERMODE_CRYPTO_MANAGEMENT
#include "header/usermod_cryptomanagement.h"
#endif
#ifndef _GENERAL
#include "header/general.h"
#endif

void usermode_aes(int argc, char** argv){
  printf("aes \n");
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
  exit(0);
}
void usermode_list_streamcipher(int argc, char** argv){
  printf("%s \n", "CRYPTO USERMODE LIST STREAM CIPHERS");
  exit(0);
}
void usermode_crypto_help(int argc, char** argv){
  printf("%s \n", "USERMOD CRYPTO HELP SECTION");
  exit(0);
}
