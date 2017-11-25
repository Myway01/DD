#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <pthread.h>

#include "socketAPI.h"

class TcpServer
{
    public:
        TcpServer(char *ip, unsigned short port);
        virtual ~TcpServer();

        int state;
        void Serve();
        /*bool Init();
        bool Listen();
        bool Accept();
        ssize_t Recv(char *recvbuf, size_t len);
        bool Send(char *sendbuf, int len);*/

    protected:

    private:
        int listenfd;

};

#endif // TCPSERVER_H
