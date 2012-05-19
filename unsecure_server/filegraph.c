#ifndef _GENERAL
#include "header/general.h"
#endif
#include "header/filegraph.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include <dirent.h>

/**
-1 not a directory

*/
int construct_graph(char *root){
  printf("DEBUG: root-dir: %s \n",root);
  DIR *root_d;
  xmlDocPtr xml_document = NULL;
  xmlNode *xml_node = NULL;
  xmlNode *a_node = "a";
  struct dirent *listing;
  root_d = opendir(root);
  if(root_d != NULL){
    while(listing = readdir(root_d)){
      char *path_file = malloc(strlen(root) + strlen(listing->d_name) + 1);
      memcpy(path_file,root,strlen(root));
      memcpy(path_file + strlen(root), listing->d_name,strlen(listing->d_name)+1);
      if(opendir(path_file) == NULL){
	xml_document = xmlReadFile(path_file,NULL,0);
	if(xml_document != NULL){
	  /**
	     some test code
	  **/
	  for(xml_node = xml_document->children; xml_node != NULL; xml_node = xml_node->next){
	    printf("%s \n",xml_node->name);
	    for(a_node = xml_node->children; a_node != NULL; a_node = a_node->next){
	      printf("%s \n",a_node->name);
	    }
	  }
	  #ifdef _DEBUG
	  printf("start parsing document \n");
	  #endif
	}else{
	  printf("fout\n");
	}
	#ifdef _DEBUG
	printf("%s \n","start free-ing xmlDocument");
	#endif
	xmlFreeDoc(xml_document);
      }
    }
  }
  (void)closedir(root_d);
}

