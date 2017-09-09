#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#define MYPORT "6001"
#define MAXBUFLEN 1300

void *get_in_addr(struct sockaddr *sa)
{
if (sa->sa_family == AF_INET) {
return &(((struct sockaddr_in*)sa)->sin_addr);
}
return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
int main(int argc, char *argv[])
{
if(argc==2){
if(strcmp(argv[1], "-h")==0){
printf("\nNAME:\n\techo\n");
printf("\nSYNOPSIS:\n\t./echo\n");
printf("\nDESCRIPTION:\n\tRecieves the incoming packet from client, decrements RC value\n\tand retansmits it to the client.\n");
exit(0);
}
}
int t, k;
int sockfd;
char buff[MAXBUFLEN];
struct addrinfo hints, *servinfo, *p;
int rv;
int numbytes;
struct sockaddr_storage their_addr;
socklen_t addr_len;
char s[INET6_ADDRSTRLEN];
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
hints.ai_socktype = SOCK_DGRAM;
hints.ai_flags = AI_PASSIVE; // use my IP
if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
return 1;
}
// loop through all the results and bind to the first we can
for(p = servinfo; p != NULL; p = p->ai_next) {
if ((sockfd = socket(p->ai_family, p->ai_socktype,
p->ai_protocol)) == -1) {
perror("listener: socket");
continue;
}
if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
close(sockfd);
perror("listener: bind");
continue;
}
break;
}
if (p == NULL) {
fprintf(stderr, "listener: failed to bind socket\n");
return 2;
}
freeaddrinfo(servinfo);
printf("listener: waiting to recvfrom...\n");
addr_len = sizeof their_addr;
while(1){
if ((numbytes = recvfrom(sockfd, buff, MAXBUFLEN-1 , 0,
(struct sockaddr *)&their_addr, &addr_len)) == -1) {
perror("recvfrom");
exit(1);
}
printf("\nrecieved datagram");
t=(buff[20]-'0')*10000+(buff[21]-'0')*1000+(buff[22]-'0')*100+(buff[23]-'0')*10+(buff[24]-'0');
t--;
for(k=24; k>=20; k--){
buff[k]=(t%10)+'0';
t=t/10;
}
if ((numbytes= sendto(sockfd, buff, strlen(buff), 0,
(struct sockaddr *)&their_addr, addr_len) == -1)){
perror("talker: sendto");
exit(1);
}
printf("\nsent datagram\n");
}
close(sockfd);
return 0;
}
