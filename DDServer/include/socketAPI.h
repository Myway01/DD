#ifndef SOCKETAPI_H
#define SOCKETAPI_H

#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

ssize_t readn(int fd, char *buf, size_t num);
ssize_t writen(int fd, char *buf, size_t num);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
ssize_t readline(int sockfd, char *buf, size_t maxlen);
ssize_t writeline(int sockfd, char *buf, size_t len);
int activate_nonblock(int fd);
int deactivate_nonblock(int fd);
int connect_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds);
int write_timeout(int fd, unsigned int wait_seconds);
int read_timeout(int fd, unsigned int wait_seconds);
int accept_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds);
int server_init(char *ip, unsigned short port, int *listenfd);

#endif //SOCKETAPI
