#ifndef _GENERAL
#include "header/general.h"
#endif
#include "header/filegraph.h"
#include "libxml/HTMLparser.h"
#include "libxml/HTMLtree.h"
#include <dirent.h>

/**
-1 not a directory
**/
document_unit* links(htmlNodePtr htm_node){
  int i = 0; //index for loop usage
  int skip = 1; //skip if dependency is not in same-origin as current context
  htmlNodePtr node = NULL;
  //  xmlAttrPtr attr = NULL;
  xmlAttribute *attr = NULL;
  char *URN_http = (char*) calloc(7,sizeof(char));
  char *URN_https = (char*) calloc(8,sizeof(char));
  char *path_file_dependency = NULL;
  document_unit* result = (document_unit*) calloc(1,sizeof(document_unit));

  for(node = htm_node; node != NULL; node = node->next){
    if(node->type == XML_ELEMENT_NODE){
      if(xmlStrcasecmp(node->name,(const xmlChar*)"A") == 0 ||
	 xmlStrcasecmp(node->name,(const xmlChar*)"LINK") == 0){
	for(attr = node->properties; attr != NULL; attr = attr->next){
	  if(xmlStrcasecmp(attr->name, (const xmlChar*)"HREF") == 0){
	    //need to check if the depending document is in the same origin.
	    strncpy(URN_https,(char*)attr->children->content+0,8);
	    strncpy(URN_http,(char*)attr->children->content+0,7);

	    if(strcmp("http://",URN_http) != 0 && strcmp("https://",URN_https) != 0){
	      //if this is true, this document_unit has another dependency.
	      path_file_dependency = (char*) calloc(strlen((char*)attr->children->content),sizeof(char));
	      strcpy(path_file_dependency,(char*)attr->children->content);
	    }
	  }
	}
      }
      if(node->children != NULL){
	links(node->children);
      }
    }
  }
  return result;
}
int construct_graph(char *root){
  DIR *root_d;
  htmlDocPtr html_document = NULL;
  struct dirent *listing;

  context_unit *filestructure_start = calloc(1, sizeof(context_unit));
  /* init context_unit
 */
  filestructure_start->number_of_units = 0;
  filestructure_start->entry_point = NULL;
  root_d = opendir(root);
  if(root_d != NULL){
    while(listing = readdir(root_d)){
      char *path_file = malloc(strlen(root) + strlen(listing->d_name) + 1);
      memcpy(path_file,root,strlen(root));
      memcpy(path_file + strlen(root), listing->d_name,strlen(listing->d_name)+1);
      if(opendir(path_file) == NULL){
	
	filestructure_start->number_of_units++; //number of document units in list +1
	filestructure_start->entry_point = (document_unit*) realloc(filestructure_start->entry_point, filestructure_start->number_of_units * sizeof(document_unit));
	/* just the name, does not include "../" name */
	filestructure_start->entry_point[filestructure_start->number_of_units-1].file_handler = fopen(listing->d_name,"rt");
	filestructure_start->entry_point[filestructure_start->number_of_units-1].path = listing->d_name;
	
	/****************************************/
        /* 64 = suppress warning reports        */
	/* 32 = suppress error reports          */
	/* 1 = relax parsing 		        */
        /****************************************/

	html_document = htmlReadFile((xmlChar*)path_file,NULL,0);
	printf("starting to check: %s \n",path_file);
	if(html_document != NULL){
	  
	  htmlNodePtr root = xmlDocGetRootElement(html_document);
	  htmlNodeStatus(root,0);
	  links(root);
#ifdef _DEBUG
	  printf("start parsing document \n");
#endif
	}else{
	  printf("fout\n");
	}
#ifdef _DEBUG
	printf("%s \n","start free-ing xmlDocument");
#endif
	xmlFreeDoc(html_document);
      }
    }
  }
  (void)closedir(root_d);
}

