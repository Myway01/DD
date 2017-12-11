#include <winsock2.h>
#include <stdio.h>

#include "TcpClient.h"
#include "DDStructs.h"

#include <iostream>
using std::cout;

int main()
{
    WinsockStart();
    TcpClient *c = new TcpClient("192.168.246.128", 8001, 5);
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
    /*int ret;
    char type = 1;
    ret = c->Send(&type, 1, 3);
    struct DD_login_cli lg;
    strcpy(lg.tel, "18322303006");
    strcpy(lg.psw, "12346");
    //ret = c->Send("hello--cli", 11, 3);
    ret = c->Send((char*)&lg, sizeof(DD_login_cli), 3);
    if (ret == -2)
        cout << "sendchaoshi\n";
    //Sleep(1000);
    char buf[100];
    //ret = c->Recv(buf, 100, 3);

    ret = c->Recv(buf, 1, 3);
    cout <<"ret" << ret << std::endl;
    if (ret == -2)
        cout << "recvchaoshi\n";
    else if (ret == -1)
        cout << "weizhicuowu";
    else
        cout << (int)buf[0];
    //cout << ret;
    if (buf[0] == 0){
        cout << "true";
    }
    else if (buf[0] == -1){
        cout << "mimacuowu";
    }
    else if (buf[0] == -2){
        cout << "yonghumingcuowu";
    }*/
    int ret;
    char type = 2;
    ret = c->Send(&type, 1, 3);
    struct DD_signup_cli su;
    strcpy(su.tel, "18769363606");
    strcpy(su.psw, "456789");
    strcpy(su.nickname, "ZhangSan");
    strcpy(su.paypsw, "456789");
    ret = c->Send((char*)&su, sizeof(DD_signup_cli), 3);
    if (ret == -2)
        cout << "sendchaoshi\n";

    char r;
    ret = c->Recv(&r, 1, 0);
    if (ret == -2)
        cout << "recvchaoshi\n";
    else
        cout << (int)r;
    if (r == 0){
        cout << "zhucechenggong";
    }
    else if (r == -1){
        cout << "zhanghaoyicunzai";
    }
    else if (r == -2){
        cout << "zhuceshibai";
    }
    delete c;
    WinsockEnd();
    getchar();
    return 0;
}
