#include "TcpClient.h"
#include "socketAPI.h"

TcpClient::TcpClient(char *srvip, unsigned short srvport, unsigned int wait_seconds)
{
    state = client_init(srvip, srvport, wait_seconds, &clifd);
}

TcpClient::~TcpClient()
{
    if (clifd > 0){
        closesocket(clifd);
    }
}

int TcpClient::Send(char *buf, SIZE_T len, unsigned int wait_seconds){
    int ret;
    ret = send_timeout(clifd, wait_seconds);
    if (ret < 0)
        return ret;
    return sendline(clifd, buf, len);
}

int TcpClient::Recv(char *buf, SIZE_T maxlen, unsigned int wait_seconds){
    int ret;
    ret = recv_timeout(clifd, wait_seconds);
    if (ret < 0){
        return ret;
    }
    return recvline(clifd, buf, maxlen);
}

