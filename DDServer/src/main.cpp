#include "MySqlAPI.h"
#include "TcpServer.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using std::cout;

int main(){
    /*MySqlAPI *db = new MySqlAPI("127.0.0.1", "root", "asd123456", "test", 3306);
    if(db->open() == true){
        cout<<"true";
    }
    else
        cout<<"false";
    string s;
    db->exec("select * from t001");
    s = db->resultAtAll();
    cout << std::endl << s;
    db->close();
    */
/*
    TcpServer *s = new TcpServer("192.168.246.128", 8001);
    if (!s->Listen())
        cout << "listen fialed\n";
    if (!s->Accept())
        cout << "accept failed\n";
    char recvbuf[1024] = {0};
    int m = 5;
    while(m--){
    if (s->Recv(recvbuf, 1024) < 0)
        cout << "recv failed\n";
    else
        cout << recvbuf << '\n';
    memset(recvbuf, 0, 1024);
        }*/
    TcpServer *s = new TcpServer("192.168.246.128", 8002);
    if (s->state == 0)
        s->Serve();
    int n;
    std::cin >> n;
    return 0;
}
