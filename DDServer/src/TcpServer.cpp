#include "TcpServer.h"

TcpServer::TcpServer(unsigned short port, char *ip)
{
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    srvaddr.sin_addr.s_addr = inet_addr(ip);
}

TcpServer::~TcpServer()
{
    //dtor
}

bool TcpServer::Listen(){
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        state = 1;
        return false;
    }
    if((bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr))) < 0){
        state = 2;
        return false;
    }
    if((listen(sockfd, SOMAXCONN)) < 0){
        state = 3;
        return false;
    }
    state = 0;
    return true;
}

bool TcpServer::Accept(){
    socklen_t len = sizeof(cliaddr);
    if((connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len)) <0)
    {
        return false;
    }
    return true;
}

ssize_t TcpServer::Recv(char* recvbuf, size_t maxlen){
    return readline(connfd, recvbuf, maxlen);
}

bool TcpServer::Send(char* sendbuf, int len){
    write(connfd, sendbuf, len);
    return true;
}
