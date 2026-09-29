#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 6161


int ping(int fd, char* ip)
{
    struct sockaddr_in req;
    req.sin_family = AF_INET;
    req.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &req.sin_addr.s_addr);
    
    int res = connect(fd, (struct sockaddr *)&req, sizeof(req));

    return res;
}



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
        printf("Waiting for request ... \n");
      
        if (ping(sock_fd, "192.168.1.1") >= 0)
        {
            printf("Successful \n");
        }
        else
        {
            printf("Nah \n");
        }
        

        /*
        int new_socket = accept(sock_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if(new_socket < 0)
        {
            printf("Could not accept the request!");
            continue;
        }

        printf("Connected!\n");
        close(new_socket);
        */
        sleep(1);
    }
    
    return 0;
}