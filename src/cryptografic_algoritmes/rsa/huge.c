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
  
  //huge temp is on the stack and filled with garbage, that is way we have two calls
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
/*************************************/
/* Divide			     */
/* note: diviser will be destroyed   */
/* note: quotient will be overwriten */
/*************************************/
void divide(huge *divid, huge *divisor, huge *quotient){
  int size = 0;  
  int bit_p = 0; //keep track witch bit in quotient is being handeld
  
  //>=
  while(compare(divisor, divid) < 0){
    left_shift(divisor);
    size++;
  }

  if(quotient){
    quotient->size = (size/8)+1;
    quotient->representation = (unsigned char*) calloc(quotient->size, sizeof(unsigned char));
    memset(quotient->representation,0,quotient->size);
  }
  
  bit_p = 8 - (size % 8) - 1;
  do{
    if(compare(divisor, divid) <= 0){
      substract(divid, divisor); //divid -= divisor
      if(quotient){
	quotient->representation[(int)(bit_p / 8)] |= (0x80 >> (bit_p % 8));
      }
    }
    if(size){
      right_shift(divisor);
    }
    bit_p++;
  }while(size--);
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

void right_shift(huge *h){
	int i = 0;
	unsigned int old_carry = 0;
	unsigned int carry = 0;
	do{
	  old_carry = carry;
	  carry = (h->representation[i] & 0x01) << 7;
	  h->representation[i] = (h->representation[i] >> 1) | old_carry;
	}while(++i < h->size);
	remove_unused_lsb(h);
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
  if(carry){ //we need to keep track when there is overflow
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
  
  /****************************************************/
  /* work through the representation masking off 8bit */
  /****************************************************/
  
  mask = 0x000000FF;
  shift = 0;
  for(i = huge->size;i;i--){
    huge->representation[i-1] = (val & mask) >> shift;
    mask <<= 8;
    shift +=8;
  }
  
}
//0 if equal
//+n if h1>h2
//-n if h1<h2
int compare(huge *h1, huge *h2){
	int i = 0;
	int j = 0;
	if(h1->size > h2->size)
		return 1;
	if(h1->size < h2->size)
		return -1;
	while(h1->representation[i] < h2->representation[j]){
		if(h1-representation[i] < h2->representation[j])
			return -1;
		else if(h1->representation[i] < h2->representation[j])
			return 1;
		j++;
		i++;
	}

  return 0; //equal
}
