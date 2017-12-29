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

	while(1){//如果超时继续读取
        if((ret = read_timeout(connfd, 45)) < 0){
            close(connfd);
            break;
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
                case DD_HEART: proc_test(connfd); break;

                case DD_LOGIN_CLI: proc_login_cli(connfd); break;
                case DD_SIGNUP_CLI: proc_signup_cli(connfd); break;
                case DD_GETCARS_CLI: proc_getcars_cli(connfd); break;
                case DD_SETSTARTPOS_CLI: proc_setstartpos_cli(connfd); break;
                case DD_DELSTARTPOS_CLI: proc_delstartpos_cli(connfd); break;
                case DD_CHECKORD_CLI: proc_checkord_cli(connfd); break;
                case DD_SENDPOS_CLI: proc_sendpos_cli(connfd); break;
                case DD_DELORDPOS_CLI: proc_delpos_cli(connfd); break;
                case DD_PAY_CLI: proc_pay_cli(connfd); break;

                case DD_LOGIN_DRV: proc_login_drv(connfd); break;
                case DD_SIGNUP_DRV: proc_signup_drv(connfd); break;
                case DD_LISTEN_DRV: proc_listen_drv(connfd); break;
                case DD_DELPOS_DRV: proc_delpos_drv(connfd); break;
                case DD_SENDSTATE_DRV: proc_sendstate_drv(connfd); break;
                case DD_SENDPOS_DRV: proc_sendpos_drv(connfd); break;
                case DD_GETINFO_DRV: proc_getinfo_drv(connfd); break;
            }
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
