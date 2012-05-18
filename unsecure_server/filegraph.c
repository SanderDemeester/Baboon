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
    while(listing = readdir(root_d)){
      char *path_file = malloc(strlen(root) + strlen(listing->d_name) + 1);
      memcpy(path_file,root,strlen(root));
      memcpy(path_file + strlen(root), listing->d_name,strlen(listing->d_name)+1);
      FILE *file = fopen(path_file,"rb");
      char line[100] = {0};
      if(file != NULL){
	while(fscanf(file,"%s",&line) == 1){
	  printf("%s \n",line);
	}
      }else{
	printf("fout\n");
      }
    }
    (void)closedir(root_d);
  }
}

