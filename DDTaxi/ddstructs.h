#ifndef DDSTRUCTS_H
#define DDSTRUCTS_H

#define DD_HEART 0
#define DD_LOGIN_CLI 1
#define DD_SIGNUP_CLI 2
#define DD_INFO_CLI 3
#define DD_GEO 4

//1
struct DD_login_cli{
    char tel[12];
    char psw[33];
};
//2
struct DD_signup_cli{
    char tel[12];
    char psw[33];
    char nickname[21];
    char paypsw[33];
};
//3
struct DD_info_cli{
    char nickname[24];
    char bal[12];
};
//4
struct DD_geo{
    char name[12];
    char lng[24];
    char lat[24];
};

#endif // DDSTRUCTS_H
