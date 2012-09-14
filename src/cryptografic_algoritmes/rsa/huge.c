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
    carry = sum > 0xFF; //bigger then FF? whut? well.. yes.
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
void expand(huge *huge1){
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
/********************************************************/
/* Multiply huge1, huge2 overwriting the value of huge1 */
/********************************************************/
void multiply(huge* huge1, huge* huge2){
  unsigned char mask = 0x01;
  unsigned int i;
  huge temp;
  
  set_huge(&temp, 0);
  copy_huge(&temp, huge1);
  set_huge(huge1, 0);
  
  i = huge2->size;
  do{
    i--;
    for(;;mask <<= 1){
      if(mask & huge2->representation[i]){
	add(huge1, &temp);
      }
      left_shift(&temp);
    }
  }while(i);
  
}
/*******************************************************************/
/* remove unused bits in left most handside of the binary sequence */
/*******************************************************************/
void remove_unused_lsb(huge* h){
  int i = 0;
  while(!(h->representation[i]) && (i < h->size)) i++;
  if(i && i < h->size){
    unsigned char *temp = &h->representation[i];
    h->representation = (unsigned char*) calloc(h->size - i, sizeof(unsigned char));
    memcpy(h->representation,temp, h->size-i);
    h->size-=1;
  }
}
void left_shift(huge *huge1){
  int i = huge1->size;
  int old_carry = 0;
  int carry = 0;
  do{
    i--;
    old_carry = carry;
    carry = (huge1->representation[i] & 0x80) == 0x80; //0x80 -> 128, the representation is unsigned
    huge1->representation[i] = (huge1->representation[i] << 1) | old_carry; //shift and or carry
  }while(i);
  if(carry){
    expand(huge1); 
  }
}

void copy_huge(huge *target, huge *source){
  if(target->representation){
    free(target->representation);
  }
  target->size = source->size;
  target->representation = (unsigned char*) calloc(source->size, sizeof(unsigned char));
  memcpy(target->representation, source->representation, (source->size * sizeof(unsigned char)));
      
}
void free_huge(huge *n){
  if(n->representation){
    free(n->representation);
  }
}
void set_huge(huge *huge, unsigned int val){
  unsigned int mask = 0xFF000000;
  unsigned int i = 0;
  unsigned int shift = 0;
  
  huge->size = 4; //4 bytes

  /**************************************************************/
  /* we will go in steps of 1 byte masking off the value        */
  /*   to find what the minimum size will be. We leave at least */
  /*   1 byte over					        */
  /**************************************************************/
  for(; mask > 0x000000FF; mask >>=8){
    if(val & mask) break;
    huge->size--;
  }
  
  huge->representation = (unsigned char *)malloc(huge->size);
  
}
