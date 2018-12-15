#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

FILE *output_file;
int calls_count=0;
unsigned capturing_socket, socket_size;
struct sockaddr_in recepient;

char * get_local_time ();
void print_and_save_calls (unsigned char*);
void close(unsigned);

int main()
{
    output_file=fopen("who.sthere","a");
    struct sockaddr socket_address;
    unsigned char *buffer = (unsigned char *)malloc(16);
    capturing_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    while(1)
    {
      socket_size = sizeof socket_address;
      recvfrom(capturing_socket, buffer, 16, 0, &socket_address, &socket_size);
      ++calls_count;
      print_and_save_calls(buffer);
    }
    close(capturing_socket);
    return 0;
}

char * get_local_time ()
{
  time_t time_full;
  struct tm *time_local;
  time( &time_full );
  time_local = localtime( &time_full );
  return asctime(time_local);
}

void print_and_save_calls(unsigned char* socket_buffer)
{
    struct iphdr *ip_header = (struct iphdr *)socket_buffer;
    recepient.sin_addr.s_addr = ip_header->saddr;
    printf("[#%d] %s at %s\n" , calls_count,  inet_ntoa(recepient.sin_addr), get_local_time());
    fprintf(output_file,"[#%d] %s at %s\n" , calls_count, inet_ntoa(recepient.sin_addr), get_local_time());
}
