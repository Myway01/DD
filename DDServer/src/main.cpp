#include "MySqlAPI.h"
#include "TcpServer.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using std::cout;

int main(){
    TcpServer *s = new TcpServer("192.168.246.128", 8002);
    if (s->state == 0)
        s->Serve();
    int n;
    std::cin >> n;
    return 0;
}
