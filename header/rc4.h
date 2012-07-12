#define _RC4_H
static void rc4_operate(const unsigned char *plaintext,
			int plaintext_len,
			unsigned char *cijfertext,
			unsigned char *key,
			int key_len);
