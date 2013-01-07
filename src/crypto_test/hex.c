#ifndef _GENERAL_H
#include "header/general.h"
#endif

int hex_decode( const unsigned char *input,unsigned char **decoded){
	int i;
	int len;

	if(strncmp("0x",(char*)input,2)){
	  len = strlen((char*)input)+1;
		*decoded = malloc(len);
		strcpy((char**)decoded, (char*)input);
		len--;
	}else{
	  len = (strlen((char*)input) >> 1)-1;
	  *decoded = malloc(len);
	  
	  for(i = 2; i < strlen((char*)input); i+= 2){
	    (*decoded)[((i/2)-1)] =
	      (((input[i] <= '9') ? input[i] - '0' :
		((tolower(input[i])) - 'a' + 10)) << 4) |
	      ((input[i+1] <= '9') ? input[i+1] - '0' : ((tolower(input[i+1])) - 'a' + 10));
	  }
	}
	return len;
}



void show_hex(const unsigned char *array, int len){
  while(len--){
    printf("%.02x",*array++);
  }
  printf("\n");
}
