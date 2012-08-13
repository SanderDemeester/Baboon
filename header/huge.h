#define _HUGE_G

typedef struct {
  unsigned int size; //indicates the lengte of the representation array
  unsigned char *representation; //representation of large number
} huge;

/***************************************************/
/* Add two huges - overwrite huge1 with the result */
/***************************************************/
void add(huge *huge1, huge* huge2);

/**********************/
/* expand huge struct */
/**********************/
void expaned(huge *huge1);
/*******************************************************************/
/* Go through h and see how many of the lest-most bytes are unused */
/* remove then and resize h appropriately			   */
/*******************************************************************/
void remove_unused_lsb(huge *h);

/********************************************************/
/* Multiply huge1, huge2 overwriting the value of huge1 */
/********************************************************/
void multiply(huge* huge1, huge* huge2);
