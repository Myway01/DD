#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpServer
{
    public:
        TcpServer(unsigned short port, char *ip);
        virtual ~TcpServer();

        int state = 0;
        bool Listen();
        bool Accept();
        bool Recv(char *recvbuf, int len);
        bool Send(char *sendbuf, int len);

    protected:

    private:
        int sockfd, connfd;
        struct sockaddr_in srvaddr, cliaddr;

};

#endif // TCPSERVER_H
