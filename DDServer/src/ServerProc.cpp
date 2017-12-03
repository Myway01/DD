#include "ServerProc.h"

#include <string.h>

#include "socketAPI.h"

#include <iostream>
using std::cout;

void proc_test(int connfd){
    char s[6] = "hello";
    char buf[512] = {0};
    int ret = 0;
	while(1){
		memset(buf, 0, sizeof(buf));
		ret = read_timeout(connfd, 5);
		if (ret == -2){
		continue;
		}
		else if (ret == -1)
            break;

        ret = readline(connfd, buf, 512);
        if (ret <= 0){
            break;
        }
        cout << buf << std::endl;
		ret = write_timeout(connfd, 5);
		if (ret != 0){
			break;
		}
		writeline(connfd, s, 6);
	}
	cout << connfd << "close\n";
	close(connfd);
}
