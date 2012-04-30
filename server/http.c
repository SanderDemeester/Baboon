/*none secure http client**/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * parse a url, return 0 on succes and -1 if the url is wrong
 *
*/

int parse_url(char *url,char **host, char**path){
  char *position;
  position = strstr(url,"//");
  if(!position){
    return -1;
  }

  *host = position + 2;
  position = strchr(*host,'/');
  if(!position){
    *path = NULL;
  }else{
    *position = '\0';
    *path = position + 1;
  }
  return 0;
}
