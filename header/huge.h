#define _HUGE_G

typedef struct {
  unsigned int size; //indicates the lengte of the representation array
  unsigned char *representation; //representation of large number
} huge;

/***************************************************/
/* Add two huges - overwrite huge1 with the result */
/***************************************************/
void add(huge *huge1, huge* huge2);
