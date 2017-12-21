#ifndef SERVERPROC_H_INCLUDED
#define SERVERPROC_H_INCLUDED

#include "socktype.h"

void proc_test(int connfd);
void proc_login_cli(int connfd);
void proc_signup_cli(int connfd);

#endif // SERVERPROC_H_INCLUDED
