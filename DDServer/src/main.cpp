#include <iostream>
#include <cstring>
#include <cstdio>
#include "TcpServer.h"
#include "mysql/mysql.h"//防止多线程下宕机

using std::cout;

int main(){
    mysql_library_init(0, NULL, NULL);//防止多线程下宕机
    TcpServer *s = new TcpServer("192.168.246.128", 8002);
    if (s->state == 0)
        s->Serve();
    int n;
    std::cin >> n;
    mysql_library_end();//防止多线程下宕机
    return 0;
}
