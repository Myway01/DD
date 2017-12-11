#include "MySqlConn.h"

MySqlConn::MySqlConn()
{
    mysql_init(&mysql);
    res = NULL;
}

MySqlConn::~MySqlConn()
{
    if (res != NULL){
        mysql_free_result(res);
        res = NULL;
    }
    mysql_close(&mysql);
}

void MySqlConn::open(char* host, char* user, char* password, char* database, unsigned int port){

    mysql_real_connect(&mysql, host, user, password, database, port, NULL, 0);
}

void MySqlConn::exec(char* sql){
    mysql_query(&mysql, sql);
}

void MySqlConn::getSelectRes(int* rows, int* fields){
    int r = 0;
    int f = 0;
    if (res != NULL){
        mysql_free_result(res);
        res = NULL;
    }
    res = mysql_store_result(&mysql);
    r = mysql_num_rows(res);
    *rows = r;
    f = mysql_num_fields(res);
    *fields = f;
}

void MySqlConn::getSelectRes(int* rows){
    int r = 0;
    if (res != NULL){
        mysql_free_result(res);
        res = NULL;
    }
    res = mysql_store_result(&mysql);
    r = mysql_num_rows(res);
    *rows = r;
}

char* MySqlConn::getSelectRes(){
    if (res != NULL){
        mysql_free_result(res);
        res = NULL;
    }
    res = mysql_store_result(&mysql);
    MYSQL_ROW result = mysql_fetch_row(res);
    if (result != NULL)
        return result[0];
    else
        return NULL;
}

char** MySqlConn::getNextLine(){
    return mysql_fetch_row(res);
}

int MySqlConn::getAffectedRows(){
    return mysql_affected_rows(&mysql);
}
