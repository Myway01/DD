#include <iostream>
#include <cstring>
#include <cstdio>
#include "TcpServer.h"

using std::cout;

int main(){
    TcpServer *s = new TcpServer("192.168.246.128", 8001);
    if (s->state == 0)
        s->Serve();
    int n;
    std::cin >> n;

    return 0;
}
