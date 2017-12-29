#ifndef SOCKTYPE_H_INCLUDED
#define SOCKTYPE_H_INCLUDED

#define DD_HEART 0
#define DD_LOGIN_CLI 1
#define DD_SIGNUP_CLI 2
#define DD_GETCARS_CLI 3
#define DD_SETSTARTPOS_CLI 4
#define DD_DELSTARTPOS_CLI 5
#define DD_CHECKORD_CLI 6
#define DD_DELORDPOS_CLI 7
#define DD_SENDPOS_CLI 8
#define DD_PAY_CLI 9

#define DD_LOGIN_DRV 21
#define DD_SIGNUP_DRV 22
#define DD_LISTEN_DRV 23
#define DD_DELPOS_DRV 24
#define DD_SENDSTATE_DRV 25
#define DD_SENDPOS_DRV 26
#define DD_GETINFO_DRV 27

//1
struct DD_login_cli{
    char tel[12];
    char psw[33];
};
//2
struct DD_signup_cli{
    char tel[12];
    char nickname[21];
    char psw[33];
    char paypsw[33];
};

struct DD_info_cli{
    char nickname[24];
    char bal[12];
};
//3
struct DD_geo{
    char name[12];
    char lng[24];
    char lat[24];
};
//6
struct DD_info_drv{
    char tel[12];
    char nickname[21];
    char card[20];
};
struct DD_pay_cli{
    char clitel[12];
    char drvtel[12];
    char fare[8];
    char psw[33];
};



struct DD_drvinfo{
    char nickname[21];
    char card[20];
    char bal[12];
};

struct DD_signup_drv{
    char tel[12];
    char nickname[21];
    char card[20];
    char psw[33];
    char paypsw[33];
};

#endif // SOCKTYPE_H_INCLUDED
