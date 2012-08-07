#define _USERMODE_CRYPTO_MANAGEMENT
void usermode_aes(int argc, char** argv);
void usermode_rc4(int argc, char** argv);
void usermode_des(int argc, char** argv);
void usermode_3des(int argc, char** argv);
void usermode_list_blockcipher(int argc, char** argv);
void usermode_list_streamcipher(int argc, char** argv);
void usermode_crypto_help(int argc, char** argv);
