#ifndef MYSQLAPI_H
#define MYSQLAPI_H

#include <mysql.h>  //包含MySQL所需要的头文件
#include <string>

using std::string;
class MySqlAPI
{
    public:
        MySqlAPI();
        MySqlAPI(string host, string user, string password, string database, unsigned int port);
        virtual ~MySqlAPI();
        bool open();
        void close();
        bool exec(string sql);
        string resultAt(unsigned int row, unsigned int col);
        string resultAtRow(unsigned int row);
        string resultAtCol(unsigned int col);
        string resultAtAll();

        MYSQL *socket;

        void setHost(string host);
        string getHost();
        void setUser(string user);
        string getUser();
        void setPassword(string password);
        string getPassword();
        void setDatabase(string database);
        string getDatabase();
        void setport(unsigned int port);
        unsigned int getPort();
    protected:
        MYSQL mysql;
        MYSQL_RES *res;
        string _user;
        string _password;
        string _host;
        string _database;
        unsigned int _port;
    private:
};

#endif // MYSQLAPI_H
