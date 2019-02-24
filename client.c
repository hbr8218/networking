/*
 simple echo Client
 ./client ip port
*/
/*
what is a file descriptor?

ans:

In simple words,
 when you open a file,
  the operating system creates an entry to represent that file and store the
  information about that opened file. So if there are 100 files opened in
  your OS then there will be 100 entries in OS (somewhere in kernel).
  These entries are represented by integers like (...100, 101, 102....).
  This entry number is the file descriptor. So it is just an integer number
   that uniquely represents an opened file in operating system. If your process
   opens 10 files then your Process table will have 10 entries for file
   descriptors.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<strings.h>
#include<arpa/inet.h>
#include<string.h>

#define ERROR -1
#define BUFFER 1024

int main(int argc,char **argv)
{
  struct sockaddr_in remote_server;
  int sock;
  char input[BUFFER];
  char output[BUFFER];
  int len;

  if((sock = socket(AF_INET,SOCK_STREAM,0)) == ERROR)
  {
    perror("socket");
    exit(-1);
  }

  remote_server.sin_family = AF_INET;
  remote_server.sin_port = htons(atoi(argv[2]));
  remote_server.sin_addr.s_addr = inet_addr(argv[1]);
  bzero(&remote_server.sin_zero,8);

  if((connect(sock,(struct sockaddr *)&remote_server,sizeof(struct sockaddr_in))) == ERROR)
  {
    perror("connect");
    exit(-1);
  }

  while(1)
  {
    fgets(input,BUFFER,stdin);
    send(sock,input,strlen(input),0);
    len = recv(sock,output,BUFFER,0);
    output[len] = '\0';
    printf("%s\n",output);
  }
  close(sock);
  return 0;
}
