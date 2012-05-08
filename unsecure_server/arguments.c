#include "header/arguments.h"
#ifndef _GENERAL
#define _GENERAL
#include "header/general.h"
#endif
#ifndef _ARGUMENT_H
#include "header/arguments.h"
#endif

void usage(){}
void parse_arguments(int argc, char *argv[], struct arguments *arg_){
  int opt;
  opt = getopt(argc,argv, "f:iap:");
  while(opt != -1){
    switch(opt){
    case 'f':
      arg_->f = 1;
      arg_->parameter_f = optarg;
      break;
    case 'i':
      arg_->i = 1;
      break;
    case 'a':
      arg_->a = 1;
      break;
    case 'p':
      arg_->p = 1;
      arg_->port = optarg;
    default:
      usage();
      break;
    }
    opt = getopt(argc,argv,"f:ia");
  }
}
