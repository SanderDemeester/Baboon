#define _USERMODE_CRYPTO_MANAGEMENT
#define PRIME_ID_CRYPTO_HELP 7
#define PRIME_ID_USERMOD_AES 33
#define PRIME_ID_USERMOD_3DES 26
#define PRIME_ID_USERMOD_DES 34
#define PRIME_ID_USERMOD_RC4 57
#define PRIME_ID_USERMOD_LIST_BLOCKCIPHER 10
#define PRIME_ID_USERMOD_LIST_STREAMCIPHER 15
void usermode_aes(int argc, char** argv);
void usermode_rc4(int argc, char** argv);
void usermode_des(int argc, char** argv);
void usermode_3des(int argc, char** argv);
void usermode_list_blockcipher(int argc, char** argv);
void usermode_list_streamcipher(int argc, char** argv);
void usermode_crypto_help(int argc, char** argv);
