#ifndef _GENERAL
#include "header/general.h"
#endif
#include "header/filegraph.h"
#include "libxml/HTMLparser.h"
#include "libxml/HTMLtree.h"
#include <dirent.h>
#include <sys/stat.h>

/**
-1 not a directory
**/
document_unit* links(htmlNodePtr htm_node){
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

void construct_dependency(char *path_file, struct dirent* listing, context_unit *filestructure_start){
  htmlDocPtr html_document = NULL;
  filestructure_start->number_of_units++; //number of document units in list +1
  filestructure_start->entry_point = (document_unit*) realloc(filestructure_start->entry_point, filestructure_start->number_of_units * sizeof(document_unit));
  /* just the name, does not include "../" name */
  filestructure_start->entry_point[filestructure_start->number_of_units-1].file_handler = fopen(listing->d_name,"rt");
  filestructure_start->entry_point[filestructure_start->number_of_units-1].path = listing->d_name;
  filestructure_start->entry_point[filestructure_start->number_of_units-1].number_of_links = 0;
  filestructure_start->entry_point[filestructure_start->number_of_units-1].number_of_dependency = 0;
  
  /****************************************/
  /* 64 = suppress warning reports        */
  /* 32 = suppress error reports          */
  /* 1 = relax parsing 		        */
  /****************************************/
  
  html_document = htmlReadFile((xmlChar*)path_file,NULL,97);
#ifdef _DEBUG
  printf("starting to check: %s \n",path_file);
#endif
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

int dir_re(const char *path, context_unit *filestructure_start){
  struct dirent *listing = NULL;
  struct stat fstat;
  DIR *root_d = NULL;
  size_t path_len;
  char path_file[_POSIX_PATH_MAX+1];

  if(!path) 
    return -1;
  path_len = strlen(path);
  if(!path || !path_len || (path_len > _POSIX_PATH_MAX))
    return -1;

  root_d= opendir(path);
  if(root_d == NULL)
    return -1;
  
  while((listing = readdir(root_d)) != NULL){
    if((path_len + strlen(listing->d_name) +1) > _POSIX_PATH_MAX)
      continue;

    strcpy(path_file,path);
    if(path_file[path_len -1 ] != '/')
      strcat(path_file,"/");
    strcat(path_file,listing->d_name);

    if((strcmp(listing->d_name,".") == 0) ||
       (strcmp(listing->d_name,"..") == 0))
      continue;

    if(stat(path_file,&fstat) < 0)
      continue;
    
    if(S_ISDIR(fstat.st_mode)){
      #ifdef _DEBUG
      printf("%s \n",path_file);
      #endif
	dir_re(path_file,filestructure_start);
    }else{
      #ifdef _DEBUG
      printf("%s \n",path_file);
      #endif
       construct_dependency(path_file,listing,filestructure_start); 
    }
  }
  (void)closedir(root_d);
}

int construct_graph(char *root){
  context_unit *filestructure_start = calloc(1, sizeof(context_unit));
  /* init context_unit */
  filestructure_start->number_of_units = 0;
  filestructure_start->entry_point = NULL;
  /**************************/
  /* init function pointers */
  /**************************/
  filestructure_start->fp_exist_element = exist_element;
  filestructure_start->fp_enumerate_file_graph = enumerate_file_graph;

  dir_re(root,filestructure_start);

  /*******************************************************************************************/
  /* root_d = opendir(root);								     */
  /* if(root_d != NULL){								     */
  /*   while(listing = readdir(root_d)){						     */
  /*     char *path_file = malloc(strlen(root) + strlen(listing->d_name) + 1);		     */
  /*     memcpy(path_file,root,strlen(root));						     */
  /*     memcpy(path_file + strlen(root), listing->d_name,strlen(listing->d_name)+1);	     */
  /*     printf("%s \n",path_file);							     */
  /*     if(opendir(path_file) == NULL){						     */
  /* 	construct_dependency(path_file,listing,filestructure_start);			     */
  /*     }else{										     */
  /* 	if(strcmp(".",listing->d_name) != 0 && strcmp("..",listing->d_name) != 0){	     */
  /* 	  //found subdir								     */
  /* 	  printf("%s \n",root);								     */
  /* 	  printf("%s \n",listing->d_name);						     */
  /* 	  root_d = opendir("subdir/");							     */
  /* 	  root = "subdir/";								     */
  /* 	}										     */
  /*     }										     */
  /*   }										     */
  /* }											     */
  /*******************************************************************************************/
  /* (void)closedir(root_d); */
  printf("%d \n",filestructure_start->fp_exist_element("index.html",filestructure_start));
}

/*************************/
/* methodes of filegraph */
/*************************/
 
int exist_element(char *file_path,struct context_unit* filestructure_start){
      int i,j;
      int number_of_links;
      for(i = 0;i < filestructure_start->number_of_units; i++){
      if(strcmp(file_path,filestructure_start->entry_point[i].path) == 0){
#ifdef _DEBUG
      printf("%s \n","hier1");
#endif
      return 0;
    }
      for(j = 0; j < filestructure_start->entry_point[i].number_of_links; j++){
      if(strcmp(file_path,filestructure_start->entry_point[i].links[j].path) == 0){
#ifdef _DEBUG
      printf("%s \n","hier2");
#endif
      return 0;
    }
    }
      printf("%s \n",filestructure_start->entry_point[i].path);
    }
      return -1;
    }
 
 void enumerate_file_graph(struct context_unit *filestructure_start){
      int i;
      for(i = 0;i < filestructure_start->number_of_units; i++){
      printf("%s \n",filestructure_start->entry_point[i].path);
    }
      
    }
