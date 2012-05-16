#ifndef _GENERAL
#include "header/general.h"
#endif
#include "header/filegraph.h"
#include <dirent.h>

/**
-1 not a directory

*/
int construct_graph(char *root){
  printf("DEBUG: root-dir: %s \n",root);
  DIR *root_d;
  struct dirent *listing;

}
