//specification: http://csrc.nist.gov/publications/fips/fips46-3/fips46-3.pdf
//return non-zero
#define GET_BIT (array,bit)   \ (array[(int) (bit / 8)] &   ( 0x80 >> (bit)))
#define SET_BIT (array,bit)   \ (array[(int) (bit / 8)] |=  ( 0x80 >> (bit)))
#define CLEAR_BIT (array,bit) \ (array[(int) (bit / 8)] &= ~( 0x80 >> (bit)))

static void xor(unsigned char *target, const unsigned char *source, int len){
  while(len--){
    *target++ ^= *src++;
  }
}

static void permute(unsigned char target[], const unsigned char src[], const int parmute_table[], int len){
  int i;
  for(i = 0; i < len * 8; i++){
    if(GET_BIT(src,(permute_table[i]-1)))
      SET_BIT(target,i);
    else
      CLEAR_BIT(target,i);
  }
}
