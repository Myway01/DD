#ifndef MYSQLCONN_H
#define MYSQLCONN_H

#include <mysql/mysql.h> //包含MySQL所需要的头文件

class MySqlConn
{
    public:
        MySqlConn();
        virtual ~MySqlConn();

        void open(char* host, char* user, char* password, char* database, unsigned int port);
        void exec(char* sql);
        void getSelectRes(int* rows, int* fields);
        void getSelectRes(int* rows);
        char* getSelectRes();
        char** getNextLine();
        void getAffectedRows(int* rows);

    protected:
        MYSQL mysql;
        MYSQL_RES *res;

    private:
};

#endif // MYSQLCONN_H
