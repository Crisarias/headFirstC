#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <netdb.h>

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int open_socket_for_ip(char *ip_adress, int port)
{
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Can't open socket");
    struct sockaddr_in si;
    memset(&si, 0, sizeof(si));
    si.sin_family = PF_INET;
    si.sin_port = (in_port_t)htons(port);
    si.sin_addr.s_addr = inet_addr(ip_adress);
    int result = connect(s, (struct sockaddr *) &si, sizeof(si));
    if (result == -1)
        error("Can't connect to ip");
    return  s;
}

int open_socket_for_domain_address(char *host, char *port)
{
    struct addrinfo *res;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if(getaddrinfo(host, port, &hints, &res) == -1)
        error("Can't resolve the adress");
    int s = socket(res -> ai_family,
     res -> ai_socktype, res -> ai_protocol);
    if (s == -1)
        error("Can't open socket");
    int result = connect(s, res -> ai_addr, res -> ai_addrlen);
    freeaddrinfo(res);
    if (result == -1)
        error("Can't connect to domian adress");    
    return s;
}

int say_something(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
    {
        char *errorMsg = strerror(errno);
        if (strncmp(errorMsg,"Success", sizeof(errorMsg)) != 0)
        {
            fprintf(stderr, "%s: %s\n", "Error sending message to server", errorMsg);
        }
    }
    return result;
}


int main(int argc, char const *argv[])
{
    int d_sock = open_socket_for_domain_address("en.wikipedia.org","80");
    char buf[255];

    sprintf(buf,"GET /wiki/%s http/1.1\r\n" ,argv[1]);
    say_something(d_sock, buf);

    say_something(d_sock, "Host: en.wikipedia.org\r\n\r\n");
    char rec[256];
    int bytesRcvd = recv(d_sock, rec, 255, 0);
    while (bytesRcvd)
    {
        if (bytesRcvd == -1)
            error("Can't read from server");
        
        rec[bytesRcvd] = '\0'; //Add to the end of the array to make it a valite char array.
        printf("%s", rec);
        bytesRcvd = recv(d_sock, rec, 255, 0);
    }
    close(d_sock);    
    return 0;
}
