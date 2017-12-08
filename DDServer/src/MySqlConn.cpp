#include "MySqlConn.h"

MySqlConn::MySqlConn()
{
    mysql_init(&mysql);
}

MySqlConn::~MySqlConn()
{
    mysql_free_result(res);
    mysql_close(&mysql);
}

void MySqlConn::open(char* host, char* user, char* password, char* database, unsigned int port){

    MYSQL*ret = mysql_real_connect(&mysql, host, user, password, database, port, NULL, 0);

    if (ret == NULL){
        return;
    }
    else return;
}

void MySqlConn::exec(char* sql){
    mysql_query(&mysql, sql);
}

void MySqlConn::getSelectRes(int* rows, int* fields){
    int r = 0;
    int f = 0;
    mysql_free_result(res);
    res = mysql_store_result(&mysql);
    r = mysql_num_rows(res);
    *rows = r;
    f = mysql_num_fields(res);
    *fields = f;
}

void MySqlConn::getSelectRes(int* rows){
    int r = 0;
    mysql_free_result(res);
    res = mysql_store_result(&mysql);
    r = mysql_num_rows(res);
    *rows = r;
}

char* MySqlConn::getSelectRes(){
    mysql_free_result(res);
    res = mysql_store_result(&mysql);
    MYSQL_ROW result = mysql_fetch_row(res);
    return result[0];
}

char** MySqlConn::getNextLine(){
    return mysql_fetch_row(res);
}

void MySqlConn::getAffectedRows(int* rows){
    *rows = mysql_affected_rows(&mysql);
}
