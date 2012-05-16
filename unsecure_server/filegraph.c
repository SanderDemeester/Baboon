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
  root_d = opendir(root);
  if(root_d != NULL){
    while(listing = readdir(root_d))
      //      puts(listing->d_name);
    (void)closedir(root_d);
  }
}

