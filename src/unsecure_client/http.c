/*none secure http client**/

#define HTTP_PORT 80
#define BUFFER_SIZE 255
#ifndef _GENERAL
#include "header/general.h"
#endif
#include "header/http_command.h"

/**
 * parse a url, return 0 on succes and -1 if the url is wrong
 *
*/
void display_result(int connection){
  int rev = 0;
  static char recv_buffer[ BUFFER_SIZE +1 ];
  while((rev = recv(connection,recv_buffer,BUFFER_SIZE,0))>0){
    recv_buffer[rev] = '\0';
    printf("%s",recv_buffer);
  }
  printf("\n");
}
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

int main(int argc, char* argv[]){
  int client_connection;
  char *host;
  char *path;

  struct hostent *host_name;
  struct sockaddr_in host_adr;
  
  if(argc < 2){
    fprintf(stderr, "Usage: %s: <URL>\n",argv[0]);
    return 1;
  }
  if(parse_url(argv[1],&host,&path) == -1){
    fprintf(stderr,"Error - malformed URL '%s'.\n", argv[1]);
    return 1;
  }
  printf("Connecting to host '%s'\n",host);
  
  client_connection = socket(PF_INET,SOCK_STREAM,0); //0 is my best friend.
  if(!client_connection){
    perror("Unable to create local socket :("); //:(
    return 2;
  }

  host_name = gethostbyname(host);
  if(!host_name){
    perror("Error in dns lookup");
    return 3;
  }

  //start socket
  host_adr.sin_family = AF_INET;
  host_adr.sin_port = htons(HTTP_PORT);
  
  memcpy(&host_adr.sin_addr,host_name->h_addr_list[0],
	 sizeof(struct in_addr));

  if(connect(client_connection,(struct sockaddr*)&host_adr,sizeof(host_adr))==-1){
    perror("Unable to connect to host");
    return 4;
 }
  printf("Retrieving document: '%s'\n",path);
  
  http_get(client_connection,path,host);
  http_close(client_connection,host);
  display_result(client_connection);
  printf("Shutting down");

  if(close(client_connection) == -1){
    perror("Error closing client connection");
    return 5;
  }

  return 0;
}
  
      
  
