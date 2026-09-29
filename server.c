#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 6161

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        printf("Socket is not defined!");
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    int addrlen = sizeof(address);

    bind(sock_fd, (struct sockaddr *)&address, addrlen);
    listen(sock_fd,3);
    
    
    while (1)
    {
        int new_socket = accept(sock_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if(new_socket < 0)
        {
            printf("Could not accept the request!");
            continue;
        }

        printf("Connected!\n");
        close(new_socket);
        
        sleep(1);
    }
    
    return 0;
}