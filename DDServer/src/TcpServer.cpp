#include "TcpServer.h"

#include <string.h>



#include <iostream>
using std::cout;

void proc(char *buf, int *plen){
    cout << buf << '\n';
    memset(buf, 0, *plen);
    char s[6] = "hello";
    strcpy(buf, s);
    *plen = 6;
}
void *thread_serve(void* arg){
	int connfd = 0;
	int ret = 0;
	char buf[1024];
	int buflen = 1024;
	int writelen = buflen;
	//pthread_detach(pthread_self());

	if (arg == NULL){
		return NULL;
	}
	connfd = *((int *)arg);
	delete((int *)arg);
	while(1){
		memset(buf, 0, sizeof(buf));
		ret = read_timeout(connfd, 5);
		if (ret == -2){
		continue;
		}
		else if (ret == -1)
            break;

        ret = readline(connfd, buf, buflen);
        if (ret <= 0){
            break;
        }

        writelen = buflen;
		proc(buf, &writelen);

		ret = write_timeout(connfd, 5);
		if (ret != 0){
			break;
		}
		writeline(connfd, buf, writelen);
	}
	close(connfd);
	return NULL;
}

TcpServer::TcpServer(char *ip, unsigned short port)
{
    state = server_init(ip, port, &listenfd);
}

TcpServer::~TcpServer()
{
    if (listenfd > 0)
        close(listenfd);
}
/*
bool TcpServer::Init(){
    state = 0;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        state = -1;
        return false;
    }
    if((bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr))) < 0){
        state = -2;
        return false;
    }
    if((listen(sockfd, SOMAXCONN)) < 0){
        state = -3;
        return false;
    }
    return true;
}
*/
void TcpServer::Serve(){
    int connfd;
    int ret;
    while(1){
        ret = accept_timeout(listenfd, NULL, 5);
        if (ret < 0)
            continue;
        connfd = ret;
        pthread_t tid = 0;
		int *pCon = new int;
		*pCon = connfd;
		thread_serve((void*)pCon);
		//pthread_create(&tid, NULL, thread_serve, (void *)pCon);
    }
}

/*
bool TcpServer::Listen(){
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        state = -1;
        return false;
    }
    if((bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr))) < 0){
        state = -2;
        return false;
    }
    if((listen(sockfd, SOMAXCONN)) < 0){
        state = -3;
        return false;
    }
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
*/
