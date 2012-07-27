#ifndef _GENERAL_H
#include <header/general.h>
#endif

#ifnddef _HUGE_G
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
    memcpy(huge1->representation + (huge2->size - huge1->size),temp huge1->size);
    huge->size = huge2->size;
    free(temp);
  }
}
