#ifndef SOCKTYPE_H_INCLUDED
#define SOCKTYPE_H_INCLUDED

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

#endif // SOCKTYPE_H_INCLUDED
