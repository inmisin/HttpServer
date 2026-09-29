#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6161

int ping(char *ip)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    

    struct sockaddr_in req;
    req.sin_family = AF_INET;
    req.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &req.sin_addr);

    int res = connect(fd, (struct sockaddr *)&req, sizeof(req));

    close(fd);
    return res;
}

int main()
{
    while (1)
    {
        if(ping("192.168.1.1") >= 0)
        {
            printf("Connected!");   
        }
        else
        {
            prtinf("Nah");
        }
        sleep(1);
    }

    return 0;
}