#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "socketAPI.h"

class TcpClient
{
    public:
        TcpClient(char *srvip, unsigned short srvport, unsigned int wait_seconds);
        virtual ~TcpClient();

        int state;

        int Send(char *buf, SIZE_T len, unsigned int wait_seconds);
        int Recv(char *buf, SIZE_T maxlen, unsigned int wait_seconds);

    protected:

    private:
        SOCKET clifd;
};

#endif // TCPCLIENT_H
