#ifndef CLIINFO_H
#define CLIINFO_H

//单例模式实现客户信息存储
class CliInfo
{
public:
    static CliInfo* getCliInfo();
    char tel[12];
    char nickname[24];
    char bal[12];
private:
    CliInfo();
    CliInfo(const CliInfo&);
    CliInfo& operator=(const CliInfo&);
    static CliInfo* info;
};

#endif // CLIINFO_H
