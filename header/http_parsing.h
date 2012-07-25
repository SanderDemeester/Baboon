#ifndef HTTP_PARSING_HEADER
#define HTTP_PARSING_HEADER
#define LINE_SIZE 255
#define HTTP_RESPONSE_BUF 255
#include <time.h>
void build_error_response(int connection_socket, int http_reponse_code);
void build_succes_response(int connection_socket);
void *process_http_request(int *connection_socket);
char *read_line(int connection_socket);

typedef struct http_header{
  char *accept_header; /*Accept new incoming connection*/
  char *accept_charset; /*specify */
  char *accept_encoding;
  char *accept_language;
  char *accept_datetime;
  char *authorization;
  char *cache_control;
  char *connection;
  char *cookie;
  int *content_length;
  char *content_md5;
  char *content_type;
  
  time_t *date;
  char *expect;
  char *from;
  char *host;
  char *if_match;
  char *if_modified_since;
  char *if_none_match; /* allow a 304 not modified to be returned if content did not change*/
  char *if_range; /*if this entity is unchanged, send me the parts that i'm missing */
  char *if_unmodified_since; /*send response if content is not modified */
  char *max_forwards; /**/
  char *pragma; 
  char *proxy_authorization;
  char *referer;
  char *TE;
  char *upgrade;
  char *user_agent;
  char *via;
  char *warning;
};

#endif
