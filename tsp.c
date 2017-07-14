#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <error.h>
#include <stdlib.h>
int main(){

	int fd; char mes[20]="test\0"; char buf[20]; char *str="tcp\0";
	struct sockaddr_un sr_addr;
	int test;
	sr_addr.sun_family=AF_LOCAL;
	strcpy(sr_addr.sun_path,str);
  //      sr_addr.sin_port=54321;
    //    sr_addr.sin_addr.s_addr=INADDR_LOOPBACK;


	fd=socket(AF_LOCAL, SOCK_STREAM, 0);
	test=connect(fd,(struct sockaddr *)&sr_addr,sizeof(sr_addr));
	if(test==-1){
                perror("connect");
                exit(-1);
        }
	//scanf("%s", &mes);
	test=send(fd,&mes,20,0);
	if(test==-1){
		perror("send");
		exit(-1);
	}
	test=recv(fd,&buf,20,0);
	if(test==-1){
                perror("recv");
                exit(-1);
        }

	printf("%s\n", buf);
	close(fd);
}
