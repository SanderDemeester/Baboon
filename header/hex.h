#define HEX_H_

int hex_decode( const unsigned char *input,
		unsigned char **decoded);

void show_hex(const unsigned char *array,
	      int len);

