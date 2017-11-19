#include "socketAPI.h"


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
	char *bufp = buf;
	size_t nleft = maxlen;
	while (1)
	{
		if ((ret = recv_peek(sockfd, bufp, nleft)) < 0)
			return ret;
		else if (ret == 0)
			return ret;

		nread = ret;
		int i;
		for (i = 0; i < nread; i++)
		{
			if (bufp[i] == '\n')
			{
				ret = readn(sockfd, bufp, i+1);
				if (ret != i+1)
					exit(EXIT_FAILURE);

				return ret;
			}
		}

		if (nread > nleft)
			exit(EXIT_FAILURE);

		nleft -= nread;
		ret = readn(sockfd, bufp, nread);
		if (ret != nread)
			exit(EXIT_FAILURE);

		bufp += nread;
	}
	return -1;
}
