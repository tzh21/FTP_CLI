#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <errno.h>

#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int create_addr(char ip[], int port, struct sockaddr_in *addr){
	memset(addr, 0, sizeof(addr));
	addr->sin_family = AF_INET;
	addr->sin_port = port;
	if (inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {			//转换ip地址:点分十进制-->二进制
		printf("Error inet_pton(): %s(%d)\n", strerror(errno), errno);
		return 0;
	}
	return 1;
}

int read_tcp(int fd, char *buf){
	int p = 0;
	while (1) {
		int n = read(fd, buf + p, 8191 - p);
		if (n < 0){
			printf("Error read(): %s(%d)\n", strerror(errno), errno);
			return 0;
		}
		else if (n == 0){
			break;
		}
		else{
			p += n;
			if (buf[p - 1] == '\n'){
				break;
			}
		}
	}
	return 1;
}

int write_tcp(int fd, char *buf, int len){
	int p = 0;
	while (p < len){
		int n = write(fd, buf + p, len - p);
		if (n < 0){
			printf("Error write(): %s(%d)\n", strerror(errno), errno);
			return 0;
		}
		else{
			p += n;
		}
	}
}