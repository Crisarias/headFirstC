#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

int listener_d;

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void handle_shutdown(int sig)
{
    if(listener_d)
        close(listener_d);
    fprintf(stderr, "Server close, Bye!\n");
    exit(0);
}

//Register or replace a new signal
int catch_signal(int sig, void (*handler) (int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);    
}

int open_listener_socket()
{
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1)
        error("Can't open socket");   
    return  listener_d;
}

void bind_to_port(int socket, int port)
{
     struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(int)) == -1)
        error("Can't set the reuse option on the socket");
    int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (socket == -1)
        error("Can't bind to socket");
}

void start_listening(int socket)
{
    if(listen(socket, 10) == -1) //Listen up to 10 clients at once
        error("Can't listen");
    puts("Waiting for connections");
}

int say_something(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
    {
        char *errorMsg = strerror(errno);
        if (strncmp(errorMsg,"Success", sizeof(errorMsg)) != 0)
        {
            fprintf(stderr, "%s: %s\n", "Error sending message to client", errorMsg);
        }
    }
    return result;
}

int read_in(int socket, char *buf, int len) 
{
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    while ((c>0) && (s[c-1] != '\n')) // keep reading until there are no more characters end
    { 
        s += c; slen -= c;
        c = recv(socket, s, slen, 0);
    }
    if (c < 0)
    {
        return c; //In case an error ocurred
    }
    else if (c == 0)
    {
        buf[0] = '\0'; // Nothing read, send back empty string
    }
    else
    {
        s[c-1] = '\0'; // Replace the \r character with a \0
    }    
}


int main(int argc, char const *argv[])
{
    if (catch_signal(SIGINT, handle_shutdown) == -1)
    {
        error("Can't map the exit handler");
    }

    //Create the socket
    listener_d = open_listener_socket();
    //Bind the socket
    bind_to_port(listener_d, 30000);
    //Start Listening
    start_listening(listener_d);
    //Accept messages
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    char buf[255];
    while (1)
    {        
        int connect_d = accept(listener_d, (struct sockaddr * ) &client_addr, &address_size);

        if (connect_d == -1)
            error("Can't open secondary socket");

        if (!fork())//Create a child process for each client
        {
            close(listener_d); //In the child we dont need the server socket
            if (say_something(connect_d,
            "Internet knock_knock Protocol Server\r\nVersion 1.0\r\nKnock! Knock!\r\n") != -1)
            {
                read_in(connect_d, buf, sizeof(buf));

                if (strncasecmp("Who's there?", buf, 12))
                    say_something(connect_d, "You should say Who's there?");            
                else
                {
                    if (say_something(connect_d,
                    "Oscar\r\n") != -1)
                    {
                        read_in(connect_d, buf, sizeof(buf));

                        if (strncasecmp("Oscar who?", buf, 10))
                            say_something(connect_d, "You should say Oscar who?");
                        else
                            say_something(connect_d, "Oscar silly question, you get a silly answer\r\n");
                    }                    
                }                                
            }
            close(connect_d);
            exit(0);
        }
        close(connect_d); //The main server process does not need the client socket
    }    
    return 0;
}



