#define _ARGUMENT_H
struct arguments{
  int f; //file argument enable
  char *file_directory; //argument
  int p; //port argument enable
  int *port; //port
  int v; //verbose
  int c; //config file
  char *configfile;

};

void parse_arguments(int argc, char *argv[],struct arguments* ar);

