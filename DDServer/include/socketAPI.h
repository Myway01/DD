#ifndef SOCKETAPI_H
#define SOCKETAPI_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>

ssize_t readn(int fd, char *buf, size_t num);
ssize_t writen(int fd, char *buf, size_t num);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
ssize_t readline(int sockfd, char *buf, size_t maxlen);

#endif //SOCKETAPI
