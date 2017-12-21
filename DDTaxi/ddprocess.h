#ifndef DDPROCESS_H
#define DDPROCESS_H

#include "TcpClient.h"
#include "DDstructs.h"
#include <QString>
#define DD_INTERNETERR 321 //网络错误

int signinCli(const QString &username, const QString &password);

#endif // DDPROCESS_H
