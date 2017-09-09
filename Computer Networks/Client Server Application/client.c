#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/time.h>
#include<sys/poll.h>
#include<string.h>
#define SERVERPORT "6001"
#define MAXBUFLEN 1300

int main(int argc, char *argv[])
{
int sid;
unsigned long tim;
int t;


int k, count;

struct timeval tv;
struct pollfd fd;
int res;

unsigned long tt;
int sockfd;
struct addrinfo hints, *servinfo, *p;
int rv;
unsigned long wr;
unsigned long curr;
int numbytes;
char *help="-h";
if(strcmp(argv[1], help)==0){
printf("\nNAME:\n\tclient:\n");
printf("\nSYNOPSIS:");
printf("\n\t./client [ip address] [packet size] [reflection count] [filename]\n");
printf("\nDESCRIPTION:");
printf("\n\tSends the packet of size P bytes to the ip address of server with\n\trefletion count of initial value T.This reflection count is \n\tthen decremented each time packet is recieved from server and\n\tretransmitted. Finally when this T=o, difference between current time\n\tstamp and time at which packet was sent(in microsecond) is calculated\n\tand stored in Output filename.This is repeated for 50 packets.\n");

printf("\n\t[ip address]\t\tip address of the server to send packet");
printf("\n\t[reflection count]\teven non negative integer T");
printf("\n\t[packet size]\t\tpacket size in bytes");
printf("\n\t[filename]\t\toutput filename.txt to store data\n");

exit(1);
}
int x=atoi(argv[2]);
char buff[x], msg[x];
if (argc != 5) {
printf("enter valid arguements\n");
exit(1);
}
int d=atoi(argv[3]);
if((x<100)||x>1300){
printf("\nError:Packet size must be between 100-1300\n");
return 0;
}
if((d<2)||(d%2)!=0||(d>20000)){
printf("\nError:T should be non negative even integer between 2-20000\n");
return 0;
}
FILE *fp;
fp = fopen(argv[4], "a");


memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_DGRAM;
if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
return 1;
}
// loop through all the results and make a socket
for(p = servinfo; p != NULL; p = p->ai_next) {
if ((sockfd = socket(p->ai_family, p->ai_socktype,
p->ai_protocol)) == -1) {
perror("talker: socket");
continue;
}
break;
}
if (p == NULL) {
fprintf(stderr, "talker: failed to create socket\n");
return 2;
}
for(int j=1; j<=50; j++){
sid=j;
buff[1]=(sid%10)+'0';
buff[0]=(sid/10)+'0';
buff[2]='s';
gettimeofday(&tv,NULL);
tt= 1000000 *tv.tv_sec + tv.tv_usec;
tim=tt;
for(k=18; k>=3; k--){
buff[k]=(tt%10)+'0';
tt=tt/10;
}

buff[19]='s';
t=atoi(argv[3]);

for(int k=25; k<(x-1); k++){
buff[k]='a';
}
buff[(x-1)]='\0';
while(1){
for(k=24; k>=20; k--){
buff[k]=(t%10)+'0';
t=t/10;
}

if ((numbytes = sendto(sockfd, buff, strlen(buff), 0,
p->ai_addr, p->ai_addrlen)) == -1) {
perror("talker: sendto");
exit(1);
}
printf("\ndatagram %d sent\n", j);
fd.fd = sockfd;
fd.events = POLLIN;

res = poll(&fd, 1, 300); //in ms timeout

if (res == 0)
{
    printf("\nTimeout: Packet lost\n");
break;
}
else if (res == -1)
{
    printf("\nError\n");
break;
}
else
   // implies (fd.revents & POLLIN) != 0
 // we can read ...
if ((numbytes = recvfrom(sockfd, buff, 1300, 0, NULL, NULL)) <=-1) {
perror("recvfrom");
exit(1);
}

printf("datagram %d recieved\n", sid);
t=(buff[20]-'0')*10000+(buff[21]-'0')*1000+(buff[22]-'0')*100+(buff[23]-'0')*10+(buff[24]-'0');
if(t<=0){
gettimeofday(&tv,NULL);
tt=1000000 *tv.tv_sec + tv.tv_usec;
curr=tt;
wr=curr-tim;
fprintf(fp, "cumulative RTT for datagram %d of size %dB is: %lu\n", j, x, wr);
break;
}
}
}
freeaddrinfo(servinfo);
close(sockfd);
return 0;
}
