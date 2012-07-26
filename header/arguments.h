#define _ARGUMENT_H
#include <getopt.h>
struct arguments{
  int f; //file argument enable
  char *file_directory; //argument
  int p; //port argument enable
  int *port; //port
  int v; //verbose
  int c; //config file
  char *configfile;
  int crypt; //switch to usermode crypto function

};

void parse_arguments(int argc, char *argv[],struct arguments* ar);

