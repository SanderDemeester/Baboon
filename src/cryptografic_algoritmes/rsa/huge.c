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

static void substract(huge *huge1, huge *huge2){
  int i = huge1->size;
  int j = huge2->size;

  int difference; //signed.
  unsigned int borrow = 0;

  do{
    i--;
    if(j){
      j--;
      difference = huge1->representation[i] - huge1->representation[j] - borrow;
    }else{
      difference = huge1->representation[i] - borrow;
    }
    borrow = (difference < 0);
    huge1->representation[i] = difference;
  }while(i);
  if(borrow && i){
    if(!(huge1->representation[i-1])){
      //ERROR
      printf("Error, substract is negative\n");
      exit(0);
    }
    huge1->representation[i-1]--;
  }
  remove_unused_lsb(huge1);
}
/*******************************************************************/
/* remove unused bits in left most handside of the binary sequence */
/*******************************************************************/
remove_unused_lsb(huge* h){
  int i = 0;
  while(!(h->rep[i]) && (i < h->size)) i++;
  if(i && i < h->size){
    unsigned char *temp = &h->rep[i];
    h->rep = (unsigned char*) calloc(h->size - i, sizeof(unsigned char));
    memcpy(h->rep,temp, h->size-i);
  }
}
