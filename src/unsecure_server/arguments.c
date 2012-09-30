#define _DEBUG
#include "header/arguments.h"
#ifndef _GENERAL
#include "header/general.h"
#endif
#ifndef _ARGUMENT_H
#include "header/arguments.h"
#endif
#ifndef _USERMODE_CRYPTO_MANAGEMENT
#include "header/usermod_cryptomanagement.h"
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

void init_function_pointer(argument_block** crypto_handlers);

/*********************************/
 /*  Possible options for now:   */
 /* -d: backgrond	         */
 /* -f: load html files from     */
 /* -v: verbose		         */
 /* -p: port override	         */
 /* -f: file directory	         */
 /* -c: config file	         */
 /* -crypt: usermode crypto      */
 /* -s: suspres construcing graph*/
 /********************************/

void parse_arguments(int argc, char *argv[], struct arguments *arg_){
  int opt = 0;
  int option_index = 0;
  int uniq_functionpointer_identifier = 1;
  argument_block **crypto_handlers = (argument_block**) malloc(sizeof(argument_block*)*CRYPTO_OPTIONS);
  static int long_verbose_flag = 0;
  static int long_crypto_usermode_flag = 0;
  //static int long_help_flag = 0;
  static int crypto_enable_flags[CRYPTO_OPTIONS] = {1,1,1,1,1,1,1,1};
  static struct option long_optoins[]={
    { "verbose",       no_argument,        &long_verbose_flag,          1},
    { "crypto",        no_argument,  &long_crypto_usermode_flag,  1},
    { "help",          no_argument,        0,                           'h'},
    { "background",    no_argument,        0,                           'd'},
    { "port",          required_argument,  0,                           'p'},
    { "file",          required_argument,  0,                           'f'},
    { "config",        required_argument,  0,                           'c'},
    { "block-cipher",  no_argument,        &crypto_enable_flags[0],      2},
    { "blockcipher",   no_argument,        &crypto_enable_flags[0],      2},
    { "stream-cipher", no_argument,        &crypto_enable_flags[1],      3},
    { "streamcipher",  no_argument,        &crypto_enable_flags[1],      3},
    { "list",          no_argument,        &crypto_enable_flags[2],      5},
    { "help",          no_argument,        &crypto_enable_flags[3],      7},
    { "aes",           no_argument,        &crypto_enable_flags[4],      11},
    { "3des",          no_argument,        &crypto_enable_flags[5],      13},
    { "des",           no_argument,        &crypto_enable_flags[6],      17}, 
    { "rc4",           no_argument,        &crypto_enable_flags[7],      19},
  };
  for(option_index = 0; option_index < CRYPTO_OPTIONS; option_index++)
    crypto_handlers[option_index] = (argument_block*) malloc(sizeof(argument_block));

  init_function_pointer(crypto_handlers);
  option_index=0;

  opt = getopt_long(argc, argv, "sf:p:vdc:he::d::", long_optoins, &option_index);

  while(opt != -1){
    switch(opt){
    case 'f':
      arg_->f = 1;
      arg_->file_directory = optarg;
      break;
    case 'p':
      arg_->p = 1;
      arg_->port = (int*)optarg;
      break;
    case 'c':
      arg_->c = 1;
      arg_->configfile = optarg;
      break;
    case 'v':
      arg_->v = 1;
      break;
    case 'h':
      if(!long_crypto_usermode_flag){
	display_help(argv[0]);
      }else{
	crypto_enable_flags[3] = 7; 
      }
    case 's':
      arg_->s = 1;
      break;
    case 'd':
      arg_->d = 1;
    default:
      if(long_verbose_flag){ 
	arg_->v=1; 
	break;
      }
    }
    opt = getopt_long(argc, argv, "sf:p:vdc:he::d::", long_optoins, &option_index);
  }
  if(long_crypto_usermode_flag){
    arg_->crypt = 1;
    for(option_index = 0; option_index < CRYPTO_OPTIONS; option_index++){
      uniq_functionpointer_identifier *= crypto_enable_flags[option_index];
    }
    #ifdef debug
    printf("%d \n",uniq_functionpointer_identifier);
    #endif
    for(option_index = 0; option_index < CRYPTO_OPTIONS; option_index++){
      if(crypto_handlers[option_index]->value == uniq_functionpointer_identifier){
    	crypto_handlers[option_index]->function_pointer(argc,argv);
	exit(0); //stop executing proces
      }
    }
  }
}
void init_function_pointer(argument_block** crypto_handlers){
  crypto_handlers[0]->value = PRIME_ID_USERMOD_AES;
  crypto_handlers[0]->function_pointer = usermode_aes;

  crypto_handlers[1]->value = PRIME_ID_USERMOD_3DES;
  crypto_handlers[1]->function_pointer = usermode_3des;

  crypto_handlers[2]->value = PRIME_ID_USERMOD_DES;
  crypto_handlers[2]->function_pointer = usermode_des;

  crypto_handlers[3]->value = PRIME_ID_USERMOD_RC4;
  crypto_handlers[3]->function_pointer = usermode_rc4;

  crypto_handlers[4]->value = PRIME_ID_USERMOD_LIST_BLOCKCIPHER;
  crypto_handlers[4]->function_pointer = usermode_list_blockcipher;

  crypto_handlers[5]->value = PRIME_ID_USERMOD_LIST_STREAMCIPHER;
  crypto_handlers[5]->function_pointer = usermode_list_streamcipher;

  crypto_handlers[6]->value = PRIME_ID_CRYPTO_HELP;
  crypto_handlers[6]->function_pointer = usermode_crypto_help;

  crypto_handlers[7]->value = 1;
  crypto_handlers[7]->function_pointer = usermode_crypto_help;
  
}

