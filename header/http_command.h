#ifndef HTTP_COMMAND_H
#define HTTP_COMMAND
int http_get(int connection,const char *path, const char *host);
int http_close(int connection,const char *host);
#endif /*HTTP_COMMAND_H*/
