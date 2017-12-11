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

void proc_login_cli(int connfd){

    struct DD_login_cli lg = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&lg, sizeof(struct DD_login_cli));
    if (ret <= 0){
        return;
    }

    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句
    sprintf(sql, "SELECT psw FROM CLIENT WHERE tel='%s'", lg.tel);
    db.exec(sql);
    char* psw = db.getSelectRes();//查询到的密码
    char r;//回复数据
    if (psw != NULL)
        r = ((strcmp(psw, lg.psw) == 0) ? 0 : -1);//0代表成功，-1代表密码错误
    else
        r = -2;//-2代表用户不存在

    ret = write_timeout(connfd, 5);
    if (ret != 0){
        return;
    }
    writeline(connfd, &r, 1);
    cout << connfd << "end\n";
}

void proc_signup_cli(int connfd){

    struct DD_signup_cli su = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&su, sizeof(struct DD_signup_cli));
    if (ret <= 0){
        return;
    }

    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句
    sprintf(sql, "SELECT * FROM CLIENT WHERE tel='%s'", su.tel);
    db.exec(sql);
    char* id = db.getSelectRes();
    char r;//回复数据
    if (id != NULL)
        r = -1;//-1代表用户名已存在
    else {
        memset(sql, 0, 256);
        sprintf(sql, "INSERT INTO CLIENT(tel,psw,nickname,paypsw) VALUES('%s','%s','%s','%s')", su.tel, su.psw, su.nickname, su.paypsw);
        db.exec(sql);
        ret = db.getAffectedRows();
        if (ret == 1)
            r = 0;//0代表注册成功
        else
            r = -2;//-2代表注册失败
    }


    ret = write_timeout(connfd, 5);
    if (ret != 0){
        return;
    }
    writeline(connfd, &r, 1);
    cout << connfd << "closed\n";
}
