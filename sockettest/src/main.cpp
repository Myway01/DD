#include <winsock2.h>
#include <stdio.h>

#include "TcpClient.h"
#include "DDStructs.h"

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
    Sleep(10000);

    //char aa[] = "helloÄãºÃhello";
    int ret;
    char type = 1;
    ret = c->Send(&type, 1, 3);
    struct DD_login lg;
    strcpy(lg.tel, "18322303006");
    strcpy(lg.psw, "123456");
    //ret = c->Send("hello--cli", 11, 3);
    ret = c->Send((char*)&lg, sizeof(DD_login), 3);
    if (ret == -2)
        cout << "sendchaoshi\n";
    Sleep(10000);
    char buf[100] = {0};
    //ret = c->Recv(buf, 100, 3);

    ret = c->Recv(buf, 100, 0);
    if (ret == -2)
        cout << "recvchaoshi\n";
    else
        cout << buf;
    //cout << ret;
    if (buf[0] == 0){
        cout << "false";
    }
    else if (buf[0] == 1){
        cout << "true";
    }
    WinsockEnd();
    getchar();
    return 0;
}
