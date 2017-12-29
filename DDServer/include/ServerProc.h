#ifndef SERVERPROC_H_INCLUDED
#define SERVERPROC_H_INCLUDED

#include "socktype.h"

void proc_test(int connfd);
void proc_login_cli(int connfd);
void proc_signup_cli(int connfd);
void proc_getcars_cli(int connfd);
void proc_setstartpos_cli(int connfd);
void proc_delstartpos_cli(int connfd);
void proc_checkord_cli(int connfd);
void proc_sendpos_cli(int connfd);
void proc_delpos_cli(int connfd);
void proc_pay_cli(int connfd);


void proc_login_drv(int connfd);
void proc_signup_drv(int connfd);
void proc_listen_drv(int connfd);
void proc_delpos_drv(int connfd);
void proc_sendstate_drv(int connfd);
void proc_sendpos_drv(int connfd);
void proc_getinfo_drv(int connfd);

#endif // SERVERPROC_H_INCLUDED
