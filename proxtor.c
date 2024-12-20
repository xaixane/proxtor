#include "proxtor.h"

proxy_request * make_request(struct sockaddr_in* recieved_sock_point){
	
	proxy_request*  req;
	req=malloc(reqsize);
	
	req->vn = 4; //socks version = 4
	req->cd = 1; // socket mode..connect or bind. 1 forconect;
	req->dstport=recieved_sock_point->sin_port;
	req->dstip=recieved_sock_point->sin_addr.s_addr;
	strncpy(req->userid, USERNAME, 8);
	printf("\n[*]	Request Generated	");

	return req;
		    
}

int connect(int recieved_socketfd, const struct sockaddr* recieved_socket_point, socklen_t addrlen){
	int socket_fd;
	struct sockaddr_in sock_point;
	char buf[ressize];
	proxy_request* request;
	proxy_response* response;
	int (* hijack_connect)(int, const struct sockaddr*, socklen_t);

	hijack_connect=dlsym(RTLD_NEXT,"connect");
	
	socket_fd=socket(AF_INET,SOCK_STREAM,0);
	
	sock_point.sin_family=AF_INET;
	sock_point.sin_port=htons(PROXYPORT);
	sock_point.sin_addr.s_addr=inet_addr(PROXYHOST);

	if(hijack_connect(socket_fd, (struct sockaddr *)&sock_point , sizeof(sock_point))){
		perror("\nUnable to connect to proxy.........");
		return -1;
	}

	printf("\n[*]	Connected to proxy	");
	
	request=make_request((struct sockaddr_in*)recieved_socket_point);
	
	write(socket_fd,request,reqsize);
	printf("\n[*]	Request written into the socket descriptor	");
	
	memset(buf,0,ressize);
	printf("\n[*]	Buffer Memory Initiated!	");

	if(read(socket_fd,buf,ressize) < 1){
		perror("Read Failed!");
		return -1;
	}
	printf("\n[*]	Read success!	");
	response=(proxy_response*)buf;
	if(response->cd == 91){
		fprintf(stderr,"Unable to traverse through proxy!");
		free(request);
		close(socket_fd);
		return -1;
	}
	printf("\n[*]	Proxy successfully	");
	dup2(socket_fd,recieved_socketfd);
	free(request);
	return 0;
}
