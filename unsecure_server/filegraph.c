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
void links(htmlNodePtr htm_node){
  htmlNodePtr node = NULL;
  //  xmlAttrPtr attr = NULL;
  xmlAttribute *attr = NULL;
  
  for(node = htm_node; node != NULL; node = node->next){
    if(node->type == XML_ELEMENT_NODE){
      if(xmlStrcasecmp(node->name,(const xmlChar*)"A") == 0 ||
	 xmlStrcasecmp(node->name,(const xmlChar*)"LINK") == 0){
	for(attr = node->properties; attr != NULL; attr = attr->next){
	  if(xmlStrcasecmp(attr->name, (const xmlChar*)"HREF") == 0){
	    //need to check if the depending document is in the same origin.
	    printf("this page depends on: <%s>\n", attr->children->content);
	  }
	}
      }
      if(node->children != NULL){
	links(node->children);
      }
    }
  }
}
int construct_graph(char *root){
  printf("DEBUG: root-dir: %s \n",root);
  DIR *root_d;
  htmlDocPtr html_document = NULL;
  struct dirent *listing;
  root_d = opendir(root);
  if(root_d != NULL){
    while(listing = readdir(root_d)){
      printf("%s \n",root);
      char *path_file = malloc(strlen(root) + strlen(listing->d_name) + 1);
      memcpy(path_file,root,strlen(root));
      memcpy(path_file + strlen(root), listing->d_name,strlen(listing->d_name)+1);
      printf("%s \n",path_file);
      if(opendir(path_file) == NULL){
	
	/****************************************/
        /* 64 = suppress warning reports        */
	/* 1 = relax parsing 		        */
        /****************************************/

	html_document = htmlReadFile((xmlChar*)path_file,NULL,65);
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

