#include "ServerProc.h"

#include <string.h>
#include <stdio.h>

#include "socketAPI.h"
#include "socktype.h"
#include "MySqlConn.h"

#include <iostream>
using std::cout;

void proc_test(int connfd){
    char s[6] = "hello";
    char buf[512] = {0};
    int ret = 0;
	while(1){
		memset(buf, 0, sizeof(buf));
		ret = read_timeout(connfd, 5);
		if (ret == -2){
		continue;
		}
		else if (ret == -1)
            break;

        ret = readline(connfd, buf, 512);
        if (ret <= 0){
            break;
        }
        cout << buf << std::endl;
		ret = write_timeout(connfd, 5);
		if (ret != 0){
			break;
		}
		writeline(connfd, s, 6);
	}
	cout << connfd << "close\n";
	close(connfd);
}

void proc_login(int connfd){

    struct DD_login lg;
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&lg, sizeof(struct DD_login));
    if (ret <= 0){
        return;
    }

    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句
    sprintf(sql, "SELECT psw FROM DDTAXI.CLIENT WHERE tel='%s'", lg.tel);
    db.exec(sql);
    char* psw = db.getSelectRes();//查询到的密码
    if (psw != NULL)
        ret = ((strcmp(psw, lg.psw) == 0) ? 0 : -1);//0代表成功，-1代表密码错误
    else
        ret = -2;//-2代表用户不存在
    char r = ret;//回复数据

    ret = write_timeout(connfd, 5);
    if (ret != 0){
        return;
    }
    writeline(connfd, &r, 1);
    close(connfd);
    cout << connfd << "closed\n";
}
