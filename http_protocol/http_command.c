#include "header/http_command.h"
#define MAX_GET_COMMAND 255

/**
 * Send a HTTP GET request
 **/
int http_get(int connection,const char *path, const char *host){
  static char get_command[MAX_GET_COMMAND];
  /*
    The GET command is followed by a carriage-return/line-feed pair (0x0A,0x0D), CRLF-delimited
   */
  sprintf(get_command,"GET /%s HTTP/1.1\r\n",path); //http is case senstive.
  if(send(connection, get_command,strlen(get_command),0) == -1){
    return -1;
  }
  
  sprintf(get_command, "Host: %s\r\n",host); //specify the host (RFC HTTP1.1) for virtual host webservers.
  if(send(connection,get_command,strlen(get_command),0) == -1){
    return -1;
  }
  sprintf(get_command, "Connection: close\r\n\r\n");
  if(send(connection,get_command,strlen(get_command),0) == -1){
    return -1;
  }
  return 0;
}
