#define _ARGUMENT_H
struct arguments{
  int f; //file argument enable
  char *parameter_f; //argument
  int p; //port argument enable
  int *port; //port
  int i;
  int a;
};

void parse_arguments(int argc, char *argv[],struct arguments* ar);

