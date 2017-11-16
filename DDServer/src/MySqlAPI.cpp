#include "MySqlAPI.h"
#include <stdio.h>
#include <stdlib.h>

MySqlAPI::MySqlAPI(){
}
MySqlAPI::MySqlAPI(string host, string user, string password, string database, unsigned int port = 3306) : _host(host), _user(user), _password(password), _database(database), _port(port)
{
}

MySqlAPI::~MySqlAPI()
{
    //dtor
}

bool MySqlAPI::open(){
    mysql_init(&mysql);
    return mysql_real_connect(&mysql, _host.c_str(), _user.c_str(), _password.c_str(), _database.c_str(), _port, NULL, 0);
}

void MySqlAPI::close(){
    mysql_free_result(res);
    mysql_close(&mysql);
}

bool MySqlAPI::exec(string sql){
    if (mysql_query(&mysql, sql.c_str()))
        return false;
    else{
        res = mysql_store_result(&mysql);
        return true;
    }

}

string MySqlAPI::resultAt(unsigned int row, unsigned int col){
    int r = mysql_affected_rows(&mysql);
    int c = mysql_num_fields(res);
    if (row >= r || col >= c)
        return "";
    else{
        while (row){
            mysql_fetch_row(res);
            --row;
        }
        return string(mysql_fetch_row(res)[col]);
    }
}
string MySqlAPI::resultAtRow(unsigned int row){
    int r = mysql_affected_rows(&mysql);
    int c = mysql_num_fields(res);
    string s = "";
    char **result;
    if (row >= r)
        return "";
    else{
        while (row){
            mysql_fetch_row(res);
            --row;
        }
        result = mysql_fetch_row(res);
        for (int i = 0; i < c; i++){
            s += string(result[i]);
            s += "\t";
        }
        return s;
    }
}
string MySqlAPI::resultAtCol(unsigned int col){
    int r = mysql_affected_rows(&mysql);
    int c = mysql_num_fields(res);
    string s = "";
    if (col >= c)
        return "";
    else{
        while (r){
            s += string(mysql_fetch_row(res)[col]);
            s += "\n";
            --r;
        }
        return s;
    }
}
string MySqlAPI::resultAtAll(){
    int r = mysql_affected_rows(&mysql);
    int c = mysql_num_fields(res);
    string s = "";
    char **result;
    for (int i = 0; i < r; i++){
        result = mysql_fetch_row(res);
        for (int j = 0; j < c; j++){
            s += string(result[j]);
            s += "\t";
        }
        s += "\n";
    }
        return s;

}

void MySqlAPI::setHost(string host){
    _host = host;
    return;
}
string MySqlAPI::getHost(){
    return _host;
}
void MySqlAPI::setUser(string user){
    _user = user;
    return;
}
string MySqlAPI::getUser(){
    return _user;
}
void MySqlAPI::setPassword(string password){
    _password = password;
    return;
}
string MySqlAPI::getPassword(){
    return _password;
}
void MySqlAPI::setDatabase(string database){
    _database = database;
    return;
}
string MySqlAPI::getDatabase(){
    return _database;
}
void MySqlAPI::setport(unsigned int port){
    _port = port;
    return;
}
unsigned int MySqlAPI::getPort(){
    return _port;
}
