#ifndef HTTP_PARSING_HEADER
#define HTTP_PARSING_HEADER
#define LINE_SIZE 255
#define NULL 0
void build_error_response(int connection_socket, int http_reponse_code);
void build_succes_response(int connection_socket);
void *process_http_request(int *connection_socket);
char *read_line(int connection_socket);

#endif
