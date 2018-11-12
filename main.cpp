#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		printf("create socket failed\n");
		return -1;
	}
	
	struct sockaddr_in addr_serv;
	int len;
	memset(&addr_serv, 0, sizeof(struct sockaddr_in));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_port = htons(8000);
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(addr_serv);
	if(bind(sock, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) < 0)
	{
		printf("sock bind failed \n");
		return -2;
	}
	int recv_num;
	int send_num;
	char send_buf[20] = "I am server!";
	char recv_buf[20000];
	struct sockaddr_in addr_client;
	while(1){
		printf("server wait:\n");
		recv_num = recvfrom(sock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr_client, (socklen_t*)&len);
		if(recv_num < 0){
			printf("recvfrom error\n");
			exit(1);
		}
		recv_buf[recv_num] = '\0';
		printf("server receive %d bytes: %s\n", recv_num, recv_buf);
		send_num = sendto(sock, send_buf, recv_num, 0, (struct sockaddr *)&addr_client, len);
		if(send_num < 0){
			printf("sendto error \n");
			exit(1);
		}
	}
	close(sock);
	return 0;
}
