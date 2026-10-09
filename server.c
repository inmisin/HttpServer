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

    // adrese bağlanma
    if(bind(sock_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        return 1;
    }
    // adresin dinlenmesi, bağlanmadan doğrudan dinlenme yapılamaz!
    listen(sock_fd,3);
    
    char resBuffer[1024] = "HTTP/1.1 200 OK \r\nContent-Type: text/html; charset=utf-8 \r\n\r\nMerhaba!";

    
    while (1)
    {
        int new_socket = accept(sock_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if(new_socket < 0)
        {
            printf("Could not accept the request!");
            continue;
        }
        
        write(new_socket, resBuffer, 1024);
        printf("Connected!\n");
        close(new_socket);
        
        sleep(1);
    }
    
    return 0;
}