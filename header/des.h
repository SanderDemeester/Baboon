#define _DES_H
//return non-zero
/***********/
/* MACRO'S */
/***********/
#define GET_BIT(array, bit)   (array[(int) (bit/8)] & (0x80 >> (bit % 8)))
#define SET_BIT(array, bit)   (array[(int) (bit / 8)] |=  (0x80 >> (bit % 8)))
#define CLEAR_BIT(array, bit) (array[(int) (bit / 8)] &= ~(0x80 >> (bit % 8)))

#define DES_BLOCK_SIZE 8 //64 bits, defined in DES standard
#define DES_KEY_SIZE 8 //57 bits used. 64 needed. those 8 bits are used for parity checking (the good old days?), we simply ignore the 8th bits in each byte of our "working block" 
#define PC1_KEY_SIZE 7
#define SUBKEY_SIZE 6
#define EXPANSION_BLOCK_SIZE 6


/*********************************************************************/
/* Overwirtes the target array with the XOR of it and the src array. */
/*********************************************************************/
static void xor(unsigned char *target, const unsigned char *source, int len);


/********************************************************************/
/* Depending on the permute_table, this is the "<3" of our DES code.
 permute table SHOULD have exactly les and les * 8 number of entries.
 copy the second bit of the last byte into the first bit of the first byte of the output.
 the first byte of output comes from the second bits of each input byte.
 the second byte of output comes rom the fouth bits of each input byte
 You see where this is goning..
/********************************************************************/
static void permute(unsigned char target[], const unsigned char src[], const int parmute_table[], int len);

static void rotate_left(unsigned char *target);

static void des_block_operate(const unsigned char plaintext[DES_BLOCK_SIZE],
			      unsigned char ciphertext[DES_BLOCK_SIZE],
			      const unsigned char key[DES_KEY_SIZE]);