#ifndef _GENERAL_H
#include <header/general.h>
#endif

#ifndef _HUGE_G
#include <header/huge.h>
#endif

/***************************************************/
/* Add two huges - overwrite huge1 with the result */
/***************************************************/
void add(huge *huge1, huge* huge2){
  unsigned int i;
  unsigned int j;
  unsigned int sum;
  unsigned int carry = 0;

  //Adding huge2 to huge1, If huge2 > huge1 to begin with: resize huge1
  if(huge2->size > huge1->size){
    unsigned char *temp = huge1->representation;
    huge1->representation = (unsigned char *) calloc(huge2->size,
						     sizeof(unsigned char));
    memcpy(huge1->representation + (huge2->size - huge1->size),temp,huge1->size);
    huge1->size = huge2->size;
    free(temp);
  }

  i = huge1->size;
  j = huge2->size;

  do{
    i--;
    if(j){
      j--;
      sum = huge1->representation[i]+huge2->representation[j] + carry;
    }else{
      sum = huge1->representation[i] + carry;
    }
    carry = sum > 0xFF; //shift byte in
    huge1->representation[i] = sum;
  }while(i);
  if(carry){
    //still overflow, need to expand
    expand(huge1);
  }
}

/**********************/
/* expand huge struct */
/**********************/
void expaned(huge *huge1){
  unsigned char *temp = huge1->representation;
  huge1->size++;
  huge1->representation = (unsigned char*) calloc(huge1->size, sizeof(unsigned char));
  memcpy(huge1->representation + 1, temp, (huge1->size-1)*sizeof(unsigned char));
  huge1->representation[0] = 0x01;
  free(temp);
}
