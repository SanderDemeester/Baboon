
#define HTTP_PORT 80
#define MAX_CONNECTIONS 10
#ifndef _GENERAL
#include "header/general.h"
#endif
#include <ctype.h>
#include <pthread.h>
#include "header/http_parsing.h"
#include "header/arguments.h"

int main(int argc, char *argv[]){
  int listen_socket;
  int connection_socket;
  int av = 1;
  int thread_index = 0;
  int port = HTTP_PORT;
  struct sockaddr_in local_addr;
  struct sockaddr_in client_addr;
  struct arguments ar = {0,0,0,0};
  if(argc > 1){
    parse_arguments(argc,argv,&ar);
    if(ar.p == 1) port = ar.port;
  }
  if(ar.f == 1) printf("%s \n",ar.parameter_f);
  pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t)*MAX_CONNECTIONS);
  int *thread_return = (int *)malloc(sizeof(int)*MAX_CONNECTIONS);

  int client_addr_len = sizeof(client_addr);

  if((listen_socket = socket(PF_INET,SOCK_STREAM,0)) == -1){
    perror("Unable te create listen socket");
    exit(0);
  }
  
  if(setsockopt(listen_socket,SOL_SOCKET,
		SO_REUSEADDR,
		&av,sizeof(av)) == -1){
    perror("Settings socket option");
    exit(0);
  }
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(HTTP_PORT);
  local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(listen_socket,(struct sockaddr*) &local_addr,
	  sizeof(local_addr)) == -1){
    perror("Unable to bind, root?");
    exit(0);
  }
  if(listen(listen_socket,5) == -1){
    perror("Unable to set socket backlog");
    exit(0);
  }
  while((connection_socket = accept(listen_socket,
				    (struct sockaddr*)&client_addr,
				    &client_addr_len)) != -1){
    if(thread_index == MAX_CONNECTIONS){
      perror("Max connections limit is reached, wont accespt any more connections");
    }else{
    thread_return[thread_index++] = pthread_create (&threads[thread_index-1],
						    NULL,process_http_request,&connection_socket);
    }
  }
  if(connection_socket == -1){
    perror("Unable to connect socket request");
  }
  free(threads);
  free(thread_return);
  return 0;
}