#ifndef SOCKETAPI_H_INCLUDED
#define SOCKETAPI_H_INCLUDED

#include <winsock.h>
#include <basetsd.h>

SSIZE_T recvn(SOCKET fd, char *buf, SIZE_T num);
SSIZE_T sendn(SOCKET fd, char *buf, SIZE_T num);
SSIZE_T recv_peek(SOCKET sockfd, char *buf, SIZE_T len);
SSIZE_T recvline(SOCKET sockfd, char *buf, SIZE_T maxlen);
SSIZE_T sendline(SOCKET sockfd, char *buf, SIZE_T len);
int connect_timeout(SOCKET fd, struct sockaddr_in *addr, unsigned int wait_seconds);
int send_timeout(SOCKET fd, unsigned int wait_seconds);
int recv_timeout(SOCKET fd, unsigned int wait_seconds);
int accept_timeout(SOCKET fd, struct sockaddr_in *addr, unsigned int wait_seconds);
int client_init(char *srvip, unsigned short srvport, unsigned int wait_seconds, SOCKET *clifd);
int WinsockStart();
int WinsockEnd();

#endif // SOCKETAPI_H_INCLUDED
