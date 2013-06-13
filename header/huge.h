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
void expand(huge *huge1);
/*******************************************************************/
/* Go through h and see how many of the lest-most bytes are unused */
/* remove then and resize h appropriately			   */
/*******************************************************************/
void remove_unused_lsb(huge *h);

/********************************************************/
/* Multiply huge1, huge2 overwriting the value of huge1 */
/********************************************************/
void multiply(huge* huge1, huge* huge2);

/**************************/
/* copy int to byte array */
/**************************/
void set_huge(huge *h, unsigned int value);

/*********************/
/* copy huge to hyge */
/*********************/
void copy_huge(huge *target, huge *source);

/*******************************************************************/
/* remove unused bits in left most handside of the binary sequence */
/*******************************************************************/
void remove_unused_lsb(huge* h);

/*******************************************************/
/* keep track of the overflow bit and expand if needed */
/*******************************************************/
void left_shift(huge *huge1);
void right_shift(huge *h);

/****************/
/* freeing huge */
/****************/
void free_huge(huge *n);

/*******************************/
/* Copy an int to a byte array */
/*******************************/
void set_huge(huge *huge, unsigned int val);

/*************************************/
/* Divide			     */
/* note: diviser will be destroyed   */
/* note: quotient will be overwriten */
/*************************************/
void divide(huge *divid, huge *divisor, huge *quotient);
int compare(huge *h1, huge *h2);

/* raise huge to the power of exp. */
/* return result in huge */
void expon(huge*h, huge*exp);

/* Mod exponantiation  */
void mod_pow(huge*h, huge*exp, huge*n, huge*h2);
