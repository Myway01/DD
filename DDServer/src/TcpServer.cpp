#include "TcpServer.h"

#include <string.h>

#include "ServerProc.h"

#include <iostream>
using std::cout;

void *thread_serve(void* arg){
	int connfd = 0;
	int ret = 0;

	pthread_detach(pthread_self());

	if (arg == NULL){
		return NULL;
	}
	connfd = *((int *)arg);
	delete((int *)arg);
	cout << connfd <<"connect\n";

	while((ret = read_timeout(connfd, 5)) == -2);//如果超时继续读取
    if (ret == -1){
        close(connfd);
        return NULL;
    }
    char type = 0;
    ret = readline(connfd, &type, 1);
    //cout << ret << "\n";
    if (ret <= 0){
        close(connfd);
        return NULL;
    }
    else{
        switch (type){
            case 0: proc_test(connfd); break;
            case 1: proc_login_cli(connfd); break;
            case 2: proc_signup_cli(connfd); break;
        }
    }
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

void TcpServer::Serve(){
    int connfd;
    int ret;
    while(1){
        ret = accept_timeout(listenfd, NULL, 3);
        if (ret < 0)
            continue;
        connfd = ret;
        pthread_t tid = 0;
		int *pCon = new int;
		*pCon = connfd;
        //thread_serve((void *)pCon);
		pthread_create(&tid, NULL, thread_serve, (void *)pCon);
    }
}
