#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <error.h>
#include <stdlib.h>
int main(){

	int fd,fd1, test; char buf[20]; char *str="tcp\0";
	struct sockaddr_un my_addr, *addr;
	my_addr.sun_family=AF_LOCAL;
	strcpy(my_addr.sun_path,str);
//	my_addr.sin_port=54321;
//	my_addr.sin_addr.s_addr=INADDR_ANY;

        fd=socket(AF_LOCAL, SOCK_STREAM, 0);
	if(fd==-1){
		perror("socket");
		exit(-1);
	}
	test=bind(fd,(struct sockaddr*)&my_addr, sizeof(my_addr));
	if(test==-1){
		perror("bind");
		exit(-1);
	}
	listen(fd,5);
	socklen_t *len;
	fd1 = accept(fd,(struct sockaddr*)addr, len);
	if(fd1==-1){
                perror("accept");
                exit(-1);
        }
	test=recv(fd1,&buf,20,0);
	if(test==-1){
                perror("recv");
                exit(-1);
        }
	printf("%s\n", buf);
	test=send(fd1,&buf,20,0);
	if(test==-1){
                perror("send");
                exit(-1);
        }
	close(fd);
	unlink("tcp\0");
}
