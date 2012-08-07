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
  int opt = 0;
  int option_index = 0;
  int uniq_functionpointer_identifier = 1;
  static int long_verbose_flag = 0;
  static int long_crypto_usermode_flag = 0;
  static int long_help_flag = 0;
  static int crypto_enable_flags[CRYPTO_OPTIONS] = {1};
  static struct option long_optoins[]={
    { "verbose",       no_argument,        &long_verbose_flag,          1},
    { "crypto",        required_argument,  &long_crypto_usermode_flag,  1},
    { "help",          no_argument,        0,                           'h'},
    { "background",    no_argument,        0,                           'd'},
    { "port",          required_argument,  0,                           'p'},
    { "file",          required_argument,  0,                           'f'},
    { "config",        required_argument,  0,                           'c'},
    { "block-cipher",  no_argument,        &crypto_enable_flags[0],      2},
    { "stream-cipher", no_argument,        &crypto_enable_flags[1],      3},
    { "list",          no_argument,        &crypto_enable_flags[2],      5},
    { "help",          no_argument,        &crypto_enable_flags[3],      7},
    { "aes",           no_argument,        &crypto_enable_flags[4],      11},
    { "3des",          no_argument,        &crypto_enable_flags[5],      13},
    { "des",           no_argument,        &crypto_enable_flags[6],      17}, 
    { "rc4",           no_argument,        &crypto_enable_flags[7],      19},
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
  }
  if(long_crypto_usermode_flag){
    arg_->crypt = 1;
    for(option_index = 0; option_index < CRYPTO_OPTIONS; option_index++) uniq_functionpointer_identifier *= crypto_enable_flags[option_index];
    printf("%d \n", uniq_functionpointer_identifier);
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


