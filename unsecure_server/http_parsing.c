#include "header/http_parsing.h"
#ifndef _GENERAL
#include "header/general.h"
#endif
void *process_http_request(int *connection_socket){
    char *request_line;
  request_line = read_line(*connection_socket);
  if(strncmp(request_line,"GET",3)){
      build_error_response(*connection_socket,501); //HTTP 501 response
    }else{
      while(strcmp(read_line(*connection_socket), "" ));
      build_succes_response(*connection_socket);
    }
    if(close(*connection_socket) == -1){
      perror("Unable to close connection");
    }
}

void build_error_response(int connection_socket, int http_reponse_code){
  char buf[HTTP_RESPONSE_BUF];
  sprintf(buf,"HTTP/1.1 %d Error Occurred\r\n\r\n",http_reponse_code);
  if(send(connection_socket,buf,strlen(buf),0) < strlen(buf)){ //return len of buf if succes
    perror("Respond is failing..");
  }

}
void build_succes_response(int connection_socket){
  char buf[HTTP_RESPONSE_BUF];
  sprintf(buf,"HTTP/1.1 200 Success\r\nConnection: Closeo\r\nContent-Type:text\r\n\r\n<html><head><Title></Title><body>These are not the droids you're looking for.</body></html>\r\n");
  if(send(connection_socket,buf,strlen(buf),0) < strlen(buf)){
    perror("Error while sending http response");
  }
  
}
char* read_line(int connection_socket){
  static int line_lengte = LINE_SIZE;
  static char *line = NULL;
  int size;
  char c;
  int pos = 0;
  if(!line){
    line = malloc(line_lengte);
  }
  while(( size = recv(connection_socket,&c,1,0)) > 0){
    if(( c == '\n') && (line[pos - 1] == '\r' )){
      line[pos - 1] = '\0';
      break;
    }
    line[ pos++ ] = c;
    if(pos > line_lengte){
      line_lengte *= 2;
      line = realloc(line,line_lengte);
    }
  }
  return line;

}
