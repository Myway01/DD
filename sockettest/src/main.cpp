#include <winsock2.h>
#include <stdio.h>

#include "TcpClient.h"

#include <iostream>
using std::cout;

int main()
{
    WinsockStart();
    TcpClient *c = new TcpClient("192.168.246.128", 8002, 5);
    if (c->state == -2){
        cout << "lianjiechaoshi";
        WinsockEnd();
        return -1;
    }
    else if (c->state == -1){
        cout << "cuowu";
        WinsockEnd();
        return -1;
    }
    cout << "lianjiechonggong\n";
    int ret;
    ret = c->Send("hello--cli", 11, 3);
    if (ret == -2)
        cout << "sendchaoshi\n";
    char buf[100] = {0};
    ret = c->Recv(buf, 100, 3);
    if (ret == -2)
        cout << "recvchaoshi\n";
    else
        cout << buf;

    WinsockEnd();
    return 0;
}
