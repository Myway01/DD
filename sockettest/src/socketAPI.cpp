#include "socketAPI.h"

SSIZE_T recvn(SOCKET fd, char *buf, SIZE_T num){
    char *bufp = buf;
    SIZE_T nleft = num;
    SSIZE_T nrecv;
    while(nleft > 0){
        if ((nrecv = recv(fd, bufp, nleft, 0)) == SOCKET_ERROR){
            return -1;
        }
        else if (nrecv == 0)
            return num - nleft;
        else
            bufp += nrecv;
            nleft -= nrecv;
    }
    return num;
}

SSIZE_T sendn(SOCKET fd, char *buf, SIZE_T num){
    char *bufp = buf;
    SIZE_T nleft = num;
    SSIZE_T nsent;
    while(nleft > 0){
        if ((nsent = send(fd, bufp, nleft, 0)) == SOCKET_ERROR){
            return -1;
        }
        else if (nsent == 0)
            continue;
        else
            bufp += nsent;
            nleft -= nsent;
    }
    return num;
}

SSIZE_T recv_peek(SOCKET sockfd, char *buf, SIZE_T len){
    SSIZE_T ret;
    while(1){
        if ((ret = recv(sockfd, buf, len, MSG_PEEK)) == SOCKET_ERROR){
                return -1;
        }
        else
            return ret;
    }
}

SSIZE_T recvline(SOCKET sockfd, char *buf, SIZE_T maxlen){
    SSIZE_T ret;
	SSIZE_T nrecvd;
	char *bufp = buf;
	SIZE_T nleft = maxlen;
	while (1)
	{
		if ((ret = recv_peek(sockfd, bufp, nleft)) < 0)
			return ret;
		else if (ret == 0)
			return ret;

		nrecvd = ret;
		int i;
		for (i = 0; i < nrecvd; i++)
		{
			if (bufp[i] == '\r' && bufp[i+1] == '\n')
			{
				ret = recvn(sockfd, bufp, i+2);
				if (ret != i+2)
					exit(EXIT_FAILURE);

				return ret-2;
			}
		}

		if (nrecvd > nleft)
			exit(EXIT_FAILURE);

		nleft -= nrecvd;
		ret = recvn(sockfd, bufp, nrecvd);
		if (ret != nrecvd)
			exit(EXIT_FAILURE);

		bufp += nrecvd;
	}
	return -1;
}

SSIZE_T sendline(SOCKET sockfd, char *buf, SIZE_T len){
    SSIZE_T ret;
    ret = sendn(sockfd, buf, len);
    if (ret < 0)
        return ret;
    if (ret != len)
        exit(EXIT_FAILURE);
    char bufend[2] = {'\r', '\n'};
    while(sendn(sockfd, bufend, 2) != 2);
    return ret;
}

int connect_timeout(SOCKET fd, struct sockaddr_in *addr, unsigned int wait_seconds){
    int ret = 0;
    int addrlen = sizeof(struct sockaddr_in);
    if(wait_seconds > 0){
        int iMode = 1;
        ioctlsocket(fd, FIONBIO, (u_long FAR*)&iMode);
    }

    ret = connect(fd, (struct sockaddr *)addr, addrlen);
    if (ret == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK){
        fd_set connect_fdset;
        struct timeval timeout;
        FD_ZERO(&connect_fdset);
        FD_SET(fd, &connect_fdset);
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;
        ret = select(fd+1, NULL, &connect_fdset, NULL, &timeout);
        if (ret == 0){
            ret = -2;//返回值等于零时为超时
        }
        else if(ret < 0){
            ret = -1;
        }
        else if (ret == 1){
            int err;
            int socklen = sizeof(err);
            int sockoptret = getsockopt(fd, SOL_SOCKET, SO_ERROR, (char*)&err, &socklen);
            if (sockoptret == -1){
                return -1;
            }
            if (err == 0){
                ret = 0;
            }
            else{
                errno = err;
                ret = -1;
            }
        }
    }
    if (wait_seconds > 0){
        int iMode = 0;
        ioctlsocket(fd, FIONBIO, (u_long FAR*)&iMode);
    }
    return ret;
}

int send_timeout(SOCKET fd, unsigned int wait_seconds){
    int ret = 0;
    if (wait_seconds > 0){
        fd_set send_fdset;
        struct timeval timeout;

        FD_ZERO(&send_fdset);
        FD_SET(fd, &send_fdset);

        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        ret = select(fd+1, NULL, &send_fdset, NULL, &timeout);
        if (ret == 0){
            ret = -2;//返回值等于零时为超时
        }
        else if(ret < 0){
            ret = -1;
        }
        else if(ret ==1)
            ret = 0;
    }
    return ret;
}

int recv_timeout(SOCKET fd, unsigned int wait_seconds){
    int ret = 0;
    if (wait_seconds > 0){
        fd_set recv_fdset;
        struct timeval timeout;

        FD_ZERO(&recv_fdset);
        FD_SET(fd, &recv_fdset);
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        ret = select(fd+1, &recv_fdset, NULL, NULL, &timeout);
        if (ret == 0){
            ret = -2;//返回值等于零时为超时
        }
        else if(ret < 0){
            ret = -1;
        }
        else if (ret == 1)
            ret = 0;
    }
    return ret;
}

int accept_timeout(SOCKET fd, struct sockaddr_in *addr, unsigned int wait_seconds){
	int ret;
	int addrlen = sizeof(struct sockaddr_in);

	if (wait_seconds > 0){
		fd_set accept_fdset;
		struct timeval timeout;
		FD_ZERO(&accept_fdset);
		FD_SET(fd, &accept_fdset);
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;
        ret = select(fd+1, &accept_fdset, NULL, NULL, &timeout);
        if (ret == 0){
            ret = -2;//返回值等于零时为超时
        }
        else if(ret < 0){
            ret = -1;
        }
    }
	if (addr != NULL)
		ret = accept(fd, (struct sockaddr*)addr, &addrlen); //返回已连接套接字
	else
		ret = accept(fd, NULL, NULL);
    if (ret == -1){
			ret = errno;
			return ret;
    }
	return ret;
}

int client_init(char *srvip, unsigned short srvport, unsigned int wait_seconds, SOCKET *clifd){
    int ret;
    SOCKET clientSocket;
    clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if (clientSocket == INVALID_SOCKET){
        return -1;
    }

    sockaddr_in srvaddr;
    srvaddr.sin_addr.S_un.S_addr=inet_addr(srvip);
    srvaddr.sin_family=AF_INET;
    srvaddr.sin_port=htons(srvport);
    ret = connect_timeout(clientSocket, (struct sockaddr_in*)&srvaddr, wait_seconds);
    if (ret < 0){
        return ret;
    }
    *clifd = clientSocket;
    return 0;
}

int WinsockStart(){
    int err;
    WORD versionRequired;
    WSADATA wsaData;
    versionRequired=MAKEWORD(1,1);
    err = WSAStartup(versionRequired, &wsaData);
    if (err){
        return -1;//结束
    }
    return 0;
}

int WinsockEnd(){
    return WSACleanup();
}
