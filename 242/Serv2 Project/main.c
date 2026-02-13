#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <errno.h>

int main(int argc, char** argv){
        if(argc < 3){
                printf("too few arguments -- find someone to fight with\n");
                return 0;
        }
        struct addrinfo hints;
        struct addrinfo* result;


        memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    getaddrinfo(argv[1], argv[2], &hints, &result);

        int fd = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
        if( fd == -1){
                printf("socket() problem\n" );
                exit(0);
        }

        if( connect(fd,result->ai_addr,result->ai_addrlen)){
                printf("connect() problem\n");
                printf("%d\n",errno);
                exit(0);
        }

        time_t the_time = 0;

        while(1){
            int len = read(fd,&the_time,sizeof(time_t));

                the_time = ntohl(the_time);
                printf("%u\n",the_time);
                printf("%x\n",the_time);        
                char buffer[32];
                ctime_r(&the_time,buffer);
                printf("%s\n",buffer);
        }

        freeaddrinfo(result);

        close(fd);

        return 0;
}