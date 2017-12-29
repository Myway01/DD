#include <iostream>
#include <cstring>
#include <cstdio>
#include "TcpServer.h"
#include "DDredis.h"

using std::cout;

int main(){
    TcpServer *s = new TcpServer("192.168.246.128", 8001);
    if (s->state == 0)
        s->Serve();
    delete s;
    int n;
    std::cin >> n;

    /*DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->setGeo("client2", "15.134", "13.645", "test");
    r->getGeo("client3", "test");
    r->getGeoAround("15.5", "13.5", "200", "test");
    for(int i = 0; i < r->geoReslen; i++){
        cout << r->geoRes[i]->name <<": "<< r->geoRes[i]->lng <<" "<< r->geoRes[i]->lat <<"\n";
    }
    r->close();
    delete r;*/

    return 0;
}
