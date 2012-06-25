#include "header/arguments.h"
#ifndef _GENERAL
#include "header/general.h"
#endif
#ifndef _ARGUMENT_H
#include "header/arguments.h"
#endif

void display_help(char *prog_name){
  printf("Usage: %s\n",prog_name);
  printf("Options: \n");
  printf("-d: \t\t force to background\n");
  printf("-v: \t\t enable verbose output\n");
  printf("-p: \t\t port override\n");
  printf("-f: \t\t file directory to serve files from\n");
  printf("-c: \t\t specify configuration file\n");
  exit(0);
}


 /******************************/
 /*  Possible options for now: */
 /* -d: backgrond	       */
 /* -v: verbose		       */
 /* -p: port override	       */
 /* -f: file directory	       */
 /* -c: config file	       */
 /******************************/

void parse_arguments(int argc, char *argv[], struct arguments *arg_){
  int opt;
  opt = getopt(argc,argv, "f:p:vdc:");
  while(opt != -1){
    switch(opt){
    case 'f':
      arg_->f = 1;
      arg_->file_directory = optarg;
      break;
    case 'p':
      arg_->p = 1;
      arg_->port = optarg;
      break;
    case 'c':
      arg_->c = 1;
      arg_->configfile = optarg;
      break;
    case 'v':
      arg_->v = 1;
      break;
    case '?':
      display_help(argv[0]);
      break;
    default:
      display_help(argv[0]);
      break;
    }
    opt = getopt(argc,argv,"f:ia");
  }
}
