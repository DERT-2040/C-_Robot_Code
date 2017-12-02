#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT (5005u)
#define BUFSIZE (1024u)

int main(int argc, char **argv)
{
   (void)argc;
   (void)argv;
   struct sockaddr_in myaddr;
   struct sockaddr_in remaddr;
   socklen_t addrlen = sizeof(remaddr);
   int recvlen;
   int sock;
   unsigned char buf[BUFSIZE];

   /* 
   Create a UDP socket 
   AF_INET = Use the IPV4 Address Family for the UDP socket
   SOCK_DGRAM = Configure the socket to support simple datagram messages
   */
   if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
      perror("cannot create socket\n");
      return 0;
   }

   /* Bind the socket to an address/port */
   memset(&myaddr,0,sizeof(myaddr));
   myaddr.sin_family = AF_INET;
   myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   myaddr.sin_port = htons(PORT);
   if(bind(sock, reinterpret_cast<struct sockaddr *>(&myaddr),sizeof(myaddr)) < 0)
   {
      perror("bind failed");
      return 0;
   }

   /* Listen */
   setbuf(stdout, NULL);
   printf("waiting on port %u\n", PORT);
   for(;;)
   {
      /* Set flags to MSG_DONTWAIT so receive does not block if no packets are available */
      recvlen = recvfrom(sock,buf,BUFSIZE,MSG_DONTWAIT,reinterpret_cast<struct sockaddr *>(&remaddr),&addrlen);
      if(recvlen > 0)
      {
         /* Print received packet */
         buf[recvlen] = 0;
         printf("\r%s",buf);
      }
      else
      {
         /* No packet. Simulate robot loop time. */
         usleep(50000u);
      }
   }

}

