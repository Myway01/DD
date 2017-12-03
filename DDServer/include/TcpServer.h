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

    protected:

    private:
        int listenfd;

};

#endif // TCPSERVER_H
