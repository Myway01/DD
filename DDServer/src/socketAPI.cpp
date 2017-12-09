#include "socketAPI.h"

#include <string.h>


ssize_t readn(int fd, char *buf, size_t num){
    char *bufp = buf;
    size_t nleft = num;
    ssize_t nread;
    while(nleft > 0){
        if ((nread = read(fd, bufp, nleft)) < 0){
            if(errno == EINTR)
                continue;
            else
                return -1;
        }
        else if (nread == 0)
            return num - nleft;
        else
            bufp += nread;
            nleft -= nread;
    }
    return num;
}

ssize_t writen(int fd, char *buf, size_t num){
    char *bufp = buf;
    size_t nleft = num;
    ssize_t nwritten;
    while(nleft > 0){
        if ((nwritten = write(fd, bufp, nleft)) < 0){
            if(errno == EINTR)
                continue;
            else
                return -1;
        }
        else if (nwritten == 0)
            continue;
        else
            bufp += nwritten;
            nleft -= nwritten;
    }
    return num;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len){
    ssize_t ret;
    while(1){
        if ((ret = recv(sockfd, buf, len, MSG_PEEK)) < 0){
            if(errno == EINTR)
                continue;
            else
                return -1;
        }
        else
            return ret;
    }
}

ssize_t readline(int sockfd, char *buf, size_t maxlen){
    ssize_t ret;
	ssize_t nread;
	size_t nleft = maxlen + 2;
	char bufp[maxlen+2];

	while (1)
	{
        memset(bufp, 0, maxlen+2);
		if ((ret = recv_peek(sockfd, bufp, nleft)) < 0)
			return ret;
		else if (ret == 0)
			return ret;

		nread = ret;
		int i;
		for (i = 0; i < nread; i++)
		{
			if (bufp[i] == '\r' && bufp[i+1] == '\n')
			{
				ret = readn(sockfd, buf, i);
				if (ret != i)
					exit(EXIT_FAILURE);
                else if (readn(sockfd, bufp, 2) != 2)
                    exit(EXIT_FAILURE);

				return ret;
			}
		}

		if (nread > nleft)
			exit(EXIT_FAILURE);

		nleft -= nread;
		ret = readn(sockfd, buf, nread);
		if (ret != nread)
			exit(EXIT_FAILURE);

		buf += nread;
	}
	return -1;
}

ssize_t writeline(int sockfd, char *buf, size_t len){
    ssize_t ret;
    ret = writen(sockfd, buf, len);
    if (ret < 0)
        return ret;
    if (ret != len)
        exit(EXIT_FAILURE);
    char bufend[2] = {'\r', '\n'};
    while(writen(sockfd, bufend, 2) != 2);
    return ret;
}

int activate_nonblock(int fd){
    int ret = 0;
    int flag = fcntl(fd, F_GETFL);
    if (flag == -1){
        ret = flag;
        return ret;
    }

    flag |= O_NONBLOCK;
    ret = fcntl(fd, F_SETFL, flag);
    return ret;
}

int deactivate_nonblock(int fd){
    int ret = 0;
    int flag = fcntl(fd, F_GETFL);
    if (flag == -1){
        ret = flag;
        return ret;
    }

    flag &= ~O_NONBLOCK;
    ret = fcntl(fd, F_SETFL, flag);
    return ret;
}

int connect_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds){
    int ret = 0;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    if(wait_seconds > 0){
        activate_nonblock(fd);
    }

    ret = connect(fd, (struct sockaddr *)addr, addrlen);
    if (ret < 0 && errno == EINPROGRESS){
        fd_set connect_fdset;
        struct timeval timeout;
        FD_ZERO(&connect_fdset);
        FD_SET(fd, &connect_fdset);
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;
        do{
            ret = select(fd+1, NULL, &connect_fdset, NULL, &timeout);
        }while(ret < 0 && errno == EINTR);
        if (ret == 0){
            ret = -2;//返回值等于零时为超时
        }
        else if(ret < 0){
            ret = -1;
        }
        else if (ret == 1){
            int err;
            socklen_t socklen = sizeof(err);
            int sockoptret = getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &socklen);
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
        deactivate_nonblock(fd);
    }
    return ret;
}

int write_timeout(int fd, unsigned int wait_seconds){
    int ret = 0;
    if (wait_seconds > 0){
        fd_set write_fdset;
        struct timeval timeout;

        FD_ZERO(&write_fdset);
        FD_SET(fd, &write_fdset);

        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        do{
            ret = select(fd+1, NULL, &write_fdset, NULL, &timeout);
        }while(ret < 0 && errno == EINTR);
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

int read_timeout(int fd, unsigned int wait_seconds){
    int ret = 0;
    if (wait_seconds > 0){
        fd_set read_fdset;
        struct timeval timeout;

        FD_ZERO(&read_fdset);
        FD_SET(fd, &read_fdset);
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;

        do{
            ret = select(fd+1, &read_fdset, NULL, NULL, &timeout);
        }while(ret < 0 && errno == EINTR);
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

int accept_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds){
	int ret;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	if (wait_seconds > 0){
		fd_set accept_fdset;
		struct timeval timeout;
		FD_ZERO(&accept_fdset);
		FD_SET(fd, &accept_fdset);
		timeout.tv_sec = wait_seconds;
		timeout.tv_usec = 0;
		do{
			ret = select(fd+1, &accept_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);
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

int server_init(char *ip, unsigned short port, int *listenfd){
	int 	ret = 0;
	int mylistenfd;
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(ip);


	mylistenfd = socket(PF_INET, SOCK_STREAM, 0);
	if (mylistenfd < 0){
		ret = errno ;
		return ret;
	}


	int on = 1;
	ret = setsockopt(mylistenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (ret < 0){
		ret = errno ;
		return ret;
	}


	ret = bind(mylistenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (ret < 0){
		ret = errno ;
		return ret;
	}

	ret = listen(mylistenfd, SOMAXCONN);
	if (ret < 0){
		ret = errno ;
		return ret;
	}

	*listenfd = mylistenfd;

	return 0;
}
