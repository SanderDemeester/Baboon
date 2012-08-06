#define _DEBUG
#include "header/arguments.h"
#ifndef _GENERAL
#include "header/general.h"
#endif
#ifndef _ARGUMENT_H
#include "header/arguments.h"
#endif
#define CRYPTO_OPTIONS 8
/* #include <getopt.h> */

void display_help(char *prog_name){
  printf("Usage: %s\n",prog_name);
  printf("Options: \n");
  printf("-d|--background: \t\t force to background\n");
  printf("-v|--verbose: \t\t enable verbose output\n");
  printf("-p|--port: \t\t port override\n");
  printf("-f|--file: \t\t file directory to serve files from\n");
  printf("-c|--config: \t\t specify configuration file\n");
  printf("--crypto: \t\t usermode crypto\n");
  exit(0);
}

/***************************/
/* parse crypto arguments  */
/***************************/
void parse_crypto_arguments(int argc, char *argv[], int option_index){
  static int crypto_enable_flags[CRYPTO_OPTIONS];
  struct option crypto_long_option[] = {
    {"block-cipher",  no_argument, &crypto_enable_flags[0], 1},
    {"stream-cipher", no_argument, &crypto_enable_flags[1], 1},
    {"list",          no_argument, &crypto_enable_flags[2], 1},
    {"help",          no_argument, &crypto_enable_flags[3], 1},
    {"aes",           no_argument, &crypto_enable_flags[4], 1},
    {"3des",          no_argument, &crypto_enable_flags[5], 1},
    {"des",           no_argument, &crypto_enable_flags[6], 1}, 
    {"rc4",           no_argument, &crypto_enable_flags[7], 1},
  };
  
  printf("%d \n", option_index);
  while(argc > option_index){
    printf("%s \n", argv[option_index++]);
  }
}


 /******************************/
 /*  Possible options for now: */
 /* -d: backgrond	       */
 /* -f: load html files from   */
 /* -v: verbose		       */
 /* -p: port override	       */
 /* -f: file directory	       */
 /* -c: config file	       */
 /* -crypt: usermode crypto    */
 /******************************/

void parse_arguments(int argc, char *argv[], struct arguments *arg_){
  int opt;
  int c_index = 0;
  int option_index;
  static int long_verbose_flag;
  static int long_crypto_usermode_flag;
  static int long_help_flag;
  static struct option long_optoins[]={
    { "verbose", no_argument,        &long_verbose_flag,          1},
    { "crypto",  required_argument,  &long_crypto_usermode_flag,  1},
    { "help",    no_argument,        0,          'h'},
    { "background",  no_argument,        0,         'd'},
    { "port",    required_argument,  0,         'p'},
    { "file",    required_argument,  0,         'f'},
    { "config",  required_argument,  0,         'c'},
    {0,0,0,0}
  };
    
  opt = getopt_long(argc, argv, "f:p:vdc:h", long_optoins, &option_index);
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
    case 'h':
      display_help(argv[0]);
      break;
    case 'd':
      arg_->d = 1;
    default:
      if(long_verbose_flag){ 
	arg_->v=1; 
	break;
      }
    }
    opt = getopt_long(argc, argv, "f:p:vdc:h", long_optoins, &option_index);
    c_index++;
  }
  if(long_crypto_usermode_flag){
    arg_->crypt = 1;
    parse_crypto_arguments(argc, argv, c_index); 
  }
#ifdef _DEBUG
  printf("file argument    : %d \n", arg_->f);
  printf("filedir_argument : %s \n", arg_->file_directory);
  printf("port argument en : %d \n", arg_->p);
  printf("port override    : %d \n", arg_->port);
  printf("verbose          : %d \n", arg_->v);
  printf("config file enab : %d \n", arg_->c);
  printf("config file loc  : %s \n", arg_->configfile);
  printf("crytp            : %d \n", arg_->crypt);
  printf("background flag  : %d \n", arg_->d); 
  #endif
}


