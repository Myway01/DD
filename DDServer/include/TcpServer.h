#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "socketAPI.h"

class TcpServer
{
    public:
        TcpServer(unsigned short port, char *ip);
        virtual ~TcpServer();

        int state;
        bool Listen();
        bool Accept();
        ssize_t Recv(char *recvbuf, size_t len);
        bool Send(char *sendbuf, int len);

    protected:

    private:
        int sockfd, connfd;
        struct sockaddr_in srvaddr, cliaddr;

};

#endif // TCPSERVER_H
