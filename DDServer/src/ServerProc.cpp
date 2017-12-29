#include "ServerProc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "socketAPI.h"
#include "MySqlConn.h"
#include "DDredis.h"

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
    cout<<"proc_login_cli\n";
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
    char* sqlres = db.getSelectRes();//查询到的密码
    char r;//回复数据
    if (sqlres != NULL)
        r = ((strcmp(sqlres, lg.psw) == 0) ? 0 : -1);//0代表成功，-1代表密码错误
    else
        r = -2;//-2代表用户不存在

    ret = write_timeout(connfd, 5);
    if (ret < 0){
        return;
    }
    writeline(connfd, &r, 1);
    if (r == 0){//如果成功，则发送用户信息
        struct DD_info_cli info;

        memset(sql, 0, sizeof(sql));
        sprintf(sql, "SELECT nickname FROM CLIENT WHERE tel='%s'", lg.tel);
        db.exec(sql);
        sqlres = db.getSelectRes();
        if (sqlres != NULL)
            strcpy(info.nickname, sqlres);

        memset(sql, 0, sizeof(sql));
        sprintf(sql, "SELECT bal FROM CLIENT WHERE tel='%s'", lg.tel);
        db.exec(sql);
        sqlres = db.getSelectRes();
        if (sqlres != NULL)
            strcpy(info.bal, sqlres);

        ret = write_timeout(connfd, 5);
        if (ret < 0) return;
        writeline(connfd, (char*)&info, sizeof(info));
    }
    //cout << connfd << "end\n";
}

void proc_signup_cli(int connfd){
    cout<<"proc_signup_cli\n";
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
    //cout << connfd << "closed\n";
}

void proc_getcars_cli(int connfd){
    cout<<"proc_getcars_cli\n";
    struct DD_geo startgeo = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&startgeo, sizeof(struct DD_geo));
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->getGeoAround(startgeo.lng, startgeo.lat, "50", "DDDriver");
    int cars = (10<r->geoReslen? 10:r->geoReslen);//最多返回10条车辆信息
    for(int i = 0; i < cars; i++){
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, (char*)(r->geoRes[i]), sizeof(struct DD_geo));
        //cout << r->geoRes[i]->name <<": "<< r->geoRes[i]->lng <<" "<< r->geoRes[i]->lat <<"\n";
    }

    struct DD_geo retgeo = {"0", "0", "0"};//返回结束标记
    ret = write_timeout(connfd, 5);
    if (ret != 0){
        r->close();
        delete r;
        return;
    }
    writeline(connfd, (char*)&retgeo, sizeof(struct DD_geo));
    //cout << connfd << "closed\n";

    r->close();
    delete r;
}

void proc_setstartpos_cli(int connfd){
    cout<<"proc_setstartpos_cli\n";
    struct DD_geo startgeo = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&startgeo, sizeof(struct DD_geo));
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->setGeo(startgeo.name, startgeo.lng, startgeo.lat, "DDCliStart");
    char bufs[128] = {0};
    ret = read_timeout(connfd, 0);
    if (ret == -1){
        r->close();
        delete r;
        return;
    }
    ret = readline(connfd, bufs, 128);
    if (ret <= 0){
        r->close();
        delete r;
        return;
    }
    char bufe[128] = {0};
    ret = read_timeout(connfd, 0);
    if (ret == -1){
        r->close();
        delete r;
        return;
    }
    ret = readline(connfd, bufe, 128);
    if (ret <= 0){
        r->close();
        delete r;
        return;
    }

    r->setOrdPos(startgeo.name, bufs, bufe);
    r->setOrdState(startgeo.name, "0");
    //r->getOrdStartPos(startgeo.name);
    //cout << r->strRes;

    //cout << connfd << "closed\n";
    r->close();
    delete r;
}

void proc_delstartpos_cli(int connfd){
    cout<<"proc_delstartpos_cli\n";
    char tel[12] = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, tel, 12);
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->delGeo(tel, "DDCliStart");
    r->delOrd(tel);

    //cout << connfd << "closed\n";
    r->close();
    delete r;
}

void proc_checkord_cli(int connfd){
    cout<<"proc_checkord_cli\n";
    char tel[12] = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, tel, 12);
    if (ret <= 0){
        return;
    }

    char recvstate;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, &recvstate, 1);
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);

    r->getOrdState(tel);
    char state = *r->strRes;
    ret = write_timeout(connfd, 5);
    if (ret != 0){
        r->close();
        delete r;
        return;
    }
    writeline(connfd, &state, 1);
    cout << state << "state\n";

    if (state == recvstate){
        r->close();
        delete r;
        return;
    }

    if (state == '1'){
        r->delGeo(tel, "DDCliStart");
        struct DD_info_drv drvinfo = {0};
        r->getOrdDriver(tel);
        strcpy(drvinfo.tel, r->strRes);

        MySqlConn db;
        db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
        char sql[256] = {0};//sql语句
        sprintf(sql, "SELECT nickname FROM DRIVER WHERE tel='%s'", drvinfo.tel);
        db.exec(sql);
        char* res = db.getSelectRes();
        strcpy(drvinfo.nickname, res);
        //cout << drvinfo.nickname <<"\n";

        memset(sql, 0, 256);
        sprintf(sql, "SELECT card FROM DRIVER WHERE tel='%s'", drvinfo.tel);
        db.exec(sql);
        res = db.getSelectRes();
        strcpy(drvinfo.card, res);

        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, (char*)&drvinfo, sizeof(struct DD_info_drv));
    }
    else if (state == '2'){
        //r->delGeo(tel, "DDOrd");
    }
    else if (state == '3'){
        char fare[8] = {0};
        r->getOrdFare(tel);
        strcpy(fare, r->strRes);
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
    writeline(connfd, fare, 8);

    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句

    char cliname[21];
    sprintf(sql, "SELECT nickname FROM CLIENT WHERE tel='%s'", tel);
    db.exec(sql);
    strcpy(cliname, db.getSelectRes());

    char drvtel[12];
    r->getOrdDriver(tel);
    strcpy(drvtel, r->strRes);

    char drvname[21];
    memset(sql, 256, 0);
    sprintf(sql, "SELECT nickname FROM DRIVER WHERE tel='%s'", drvtel);
    db.exec(sql);
    strcpy(drvname, db.getSelectRes());

    char fee[8];
    r->getOrdFare(tel);
    strcpy(fee, r->strRes);

    char startPos[64];
    r->getOrdStartPos(tel);
    strcpy(startPos, r->strRes);

    char endPos[64];
    r->getOrdEndPos(tel);
    strcpy(endPos, r->strRes);

    memset(sql, 256, 0);
    sprintf(sql, "INSERT INTO ORDER(clitel,cliname,drvtel,drvname,time,fare,start,end) VALUES('%s','%s','%s','%s',NOW(),'%s','%s','%s')", tel, cliname, drvtel, drvname, fee, startPos, endPos);
    db.exec(sql);
    r->delOrd(tel);
    }

    //cout << connfd << "closed\n";
    r->close();
    delete r;
}

void proc_sendpos_cli(int connfd){
    cout<<"proc_sendpos_cli\n";
    struct DD_geo geo = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&geo, sizeof(struct DD_geo));
    if (ret <= 0){
        return;
    }

    char drvtel[12] = {0};
    ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, drvtel, 12);
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->setGeo(geo.name, geo.lng, geo.lat, "DDOrd");
    r->getGeo(drvtel, "DDOrd");
    ret = write_timeout(connfd, 5);
    if (ret != 0){
        r->close();
        delete r;
        return;
    }
    writeline(connfd, (char*)(r->geoRes[0]), sizeof(struct DD_geo));
    cout << r->geoRes[0]->name <<": "<< r->geoRes[0]->lng <<" "<< r->geoRes[0]->lat <<"\n";
    r->close();
    delete r;
    return;
}
void proc_delpos_cli(int connfd){
    cout<<"proc_delpos_cli\n";
    char tel[12] = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, tel, 12);
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->delGeo(tel, "DDOrd");

    //cout << connfd << "closed\n";
    r->close();
    delete r;
}
void proc_pay_cli(int connfd){
    cout<<"proc_pay_cli\n";
    struct DD_pay_cli pa = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&pa, sizeof(struct DD_pay_cli));
    if (ret <= 0){
        return;
    }

    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句
    sprintf(sql, "SELECT psw FROM CLIENT WHERE tel='%s'", pa.clitel);
    db.exec(sql);
    char* sqlres = db.getSelectRes();//查询到的密码
    char r;//回复数据
    if (strcmp(sqlres, pa.psw) != 0)
        r = -1;//-1代表密码错误
    else{
        sprintf(sql, "SELECT bal FROM CLIENT WHERE tel='%s'", pa.clitel);
        db.exec(sql);
        sqlres = db.getSelectRes();
        double rest = atof(sqlres);
        double fare = atof(pa.fare);
        if (rest < fare){
            r = -2;//-2代表余额不足
        }
        else {
            r = 0;
            sprintf(sql, "UPDATE CLIENT SET bal=bal-%s WHERE tel='%s'", pa.fare, pa.clitel);
            db.exec(sql);
            sprintf(sql, "UPDATE DRIVER SET bal=bal+%s WHERE tel='%s'", pa.fare, pa.drvtel);
            db.exec(sql);
        }
    }


    ret = write_timeout(connfd, 5);
    if (ret < 0){
        return;
    }
    writeline(connfd, &r, 1);
}






void proc_login_drv(int connfd){
    cout<<"proc_login_drv\n";
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
    sprintf(sql, "SELECT psw FROM DRIVER WHERE tel='%s'", lg.tel);
    db.exec(sql);
    char* sqlres = db.getSelectRes();//查询到的密码
    char r;//回复数据
    if (sqlres != NULL)
        r = ((strcmp(sqlres, lg.psw) == 0) ? 0 : -1);//0代表成功，-1代表密码错误
    else
        r = -2;//-2代表用户不存在

    ret = write_timeout(connfd, 5);
    if (ret < 0){
        return;
    }
    writeline(connfd, &r, 1);
    if (r == 0){//如果成功，则发送用户信息
        struct DD_drvinfo info;

        memset(sql, 0, sizeof(sql));
        sprintf(sql, "SELECT nickname FROM DRIVER WHERE tel='%s'", lg.tel);
        db.exec(sql);
        sqlres = db.getSelectRes();
        if (sqlres != NULL)
            strcpy(info.nickname, sqlres);

        memset(sql, 0, sizeof(sql));
        sprintf(sql, "SELECT card FROM DRIVER WHERE tel='%s'", lg.tel);
        db.exec(sql);
        sqlres = db.getSelectRes();
        if (sqlres != NULL)
            strcpy(info.card, sqlres);

        memset(sql, 0, sizeof(sql));
        sprintf(sql, "SELECT bal FROM DRIVER WHERE tel='%s'", lg.tel);
        db.exec(sql);
        sqlres = db.getSelectRes();
        if (sqlres != NULL)
            strcpy(info.bal, sqlres);

        ret = write_timeout(connfd, 5);
        if (ret < 0) return;
        writeline(connfd, (char*)&info, sizeof(info));
    }
    //cout << connfd << "end\n";
}

void proc_signup_drv(int connfd){
    cout<<"proc_signup_drv\n";
    struct DD_signup_drv su = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&su, sizeof(struct DD_signup_drv));
    if (ret <= 0){
        return;
    }
    cout << su.nickname << "\n";

    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句
    sprintf(sql, "SELECT * FROM DRIVER WHERE tel='%s'", su.tel);
    db.exec(sql);
    char* id = db.getSelectRes();
    char r;//回复数据
    if (id != NULL){
        r = -1;//-1代表用户名已存在
    }
    else {
        memset(sql, 0, 256);
        sprintf(sql, "INSERT INTO DRIVER(tel,psw,nickname,paypsw,card) VALUES('%s','%s','%s','%s','%s')", su.tel, su.psw, su.nickname, su.paypsw, su.card);
        db.exec(sql);
        ret = db.getAffectedRows();
        cout << ret << "here\n";
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
    //cout << connfd << "closed\n";
}

void proc_listen_drv(int connfd){
    cout<<"proc_listen_drv\n";
    struct DD_geo geo = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&geo, sizeof(struct DD_geo));
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->setGeo(geo.name, geo.lng, geo.lat, "DDDriver");

    r->getGeoAround(geo.lng, geo.lat, "5", "DDCliStart");
    int n = r->geoReslen;
    cout<<n<<"\n";
    if (n > 0){
        int i = rand() % n;
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, (char*)(r->geoRes[i]), sizeof(struct DD_geo));
        //cout << r->geoRes[i]->name <<": "<< r->geoRes[i]->lng <<" "<< r->geoRes[i]->lat <<"\n";
        char clitel[12];
        strcpy(clitel, r->geoRes[i]->name);

        char buf[128] = {0};

        r->getOrdStartPos(clitel);
        strcpy(buf, r->strRes);
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, buf, 128);

        r->getOrdEndPos(clitel);
        strcpy(buf, r->strRes);
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, buf, 128);

        MySqlConn db;
        db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
        char sql[256] = {0};//sql语句
        sprintf(sql, "SELECT nickname FROM CLIENT WHERE tel='%s'", clitel);
        db.exec(sql);
        char cliname[21] = {0};
        strcpy(cliname, db.getSelectRes());
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, cliname, 21);
    }
    else{
        struct DD_geo retgeo = {"0", "0", "0"};//返回结束标记
        ret = write_timeout(connfd, 5);
        if (ret != 0){
            r->close();
            delete r;
            return;
        }
        writeline(connfd, (char*)&retgeo, sizeof(struct DD_geo));
    }

    r->close();
    delete r;
}

void proc_delpos_drv(int connfd){
    cout<<"proc_delpos_drv\n";
    char tel[12] = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, tel, 12);
    if (ret <= 0){
        return;
    }

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->delGeo(tel, "DDDriver");

    //cout << connfd << "closed\n";
    r->close();
    delete r;
}

void proc_sendstate_drv(int connfd){
    cout<<"proc_sendstate_drv\n";
    char tel[12] = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, tel, 12);
    if (ret <= 0){
        return;
    }

    char type[2] = {0};
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, type, 1);

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    r->setOrdState(tel, type);

    char drvtel[12];
    char fare[8];
    switch (type[0]){
        case '1':
            ret = read_timeout(connfd, 0);
            if (ret == -1){
                r->close();
                delete r;
                return;
            }
            ret = readline(connfd, drvtel, 12);
            if (ret <= 0){
                r->close();
                delete r;
                return;
            }
            r->setOrdDriver(tel, drvtel);
            break;
        case '2':
            ret = read_timeout(connfd, 0);
            if (ret == -1){
                r->close();
                delete r;
                return;
            }
            ret = readline(connfd, drvtel, 12);
            if (ret <= 0){
                r->close();
                delete r;
                return;
            }
            r->delGeo(tel, "DDOrd");
            break;
        case '3':
            ret = read_timeout(connfd, 0);
            if (ret == -1){
                r->close();
                delete r;
                return;
            }
            ret = readline(connfd, fare, 8);
            if (ret <= 0){
                r->close();
                delete r;
                return;
            }
            r->setOrdFare(tel, fare);
            break;
    }

    //cout << connfd << "closed\n";
    r->close();
    delete r;
}

void proc_sendpos_drv(int connfd){
    cout<<"proc_sendpos_drv\n";
    struct DD_geo geo = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, (char*)&geo, sizeof(struct DD_geo));
    if (ret <= 0){
        return;
    }

    char clitel[12] = {0};
    ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, clitel, 12);
    if (ret <= 0){
        return;
    }
    cout<<clitel<<"\n";

    DDredis *r = new DDredis();
    r->connect("127.0.0.1", 6379);
    //cout<<"here\n";
    r->setGeo(geo.name, geo.lng, geo.lat, "DDOrd");
    //sleep(100);
    r->getGeo(clitel, "DDOrd");
    //cout<<"here\n";
    ret = write_timeout(connfd, 5);
    if (ret != 0){
        r->close();
        delete r;
        return;
    }
    cout<<"here\n";
    cout<<r->geoReslen<<"reslen\n";
    if (r->geoReslen == 1){
        writeline(connfd, (char*)(r->geoRes[0]), sizeof(struct DD_geo));
        //cout << "if\n";
        cout << r->geoRes[0]->name <<": "<< r->geoRes[0]->lng <<" "<< r->geoRes[0]->lat <<"\n";
    }
    else {
        //cout<<"else\n";
        struct DD_geo geo = {"0", "0", "0"};
        writeline(connfd, (char*)&geo, sizeof(struct DD_geo));
    }
    r->close();
    delete r;
    return;
}

void proc_getinfo_drv(int connfd){
    cout<<"proc_getinfo_drv\n";
    char tel[12] = {0};
    int ret = 0;
    ret = read_timeout(connfd, 0);
    if (ret == -1)
        return;
    ret = readline(connfd, tel, 12);
    if (ret <= 0){
        return;
    }

    char bal[12] = {0};
    MySqlConn db;
    db.open("localhost", "root", "asd123456", "DDTAXI", 3306);
    char sql[256] = {0};//sql语句
    sprintf(sql, "SELECT bal FROM DRIVER WHERE tel='%s'", tel);
    db.exec(sql);
    char* res = db.getSelectRes();
    strcpy(bal, res);

    ret = write_timeout(connfd, 5);
    if (ret != 0){
        return;
    }
    writeline(connfd, bal, 12);
}
