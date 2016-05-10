#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <string>
#include <sstream>
#include "common_socket_info.h"

class Socket{
    public:
        Socket(char hostname[], char port[], bool set_flags);
        void socket_send(char *buffer, size_t size);
        void socket_receive(char *buff, size_t size);
		void socket_receive(char *buff, size_t size, char *delim, size_t sz_delim);
        void socket_accept(Socket &connection_socket);
        bool socket_connect();
        void socket_bind();
        void socket_listen();
        void socket_shutdown(int how_flag = SHUT_RDWR);
        int getFileDescriptor();
        ~Socket();
    protected:
    private:
        char *hostname;
        char *port;
        bool set_flags;
        SocketInfo sckt_info;
        int fd;
        void setFileDescriptor(int fd);
};

#endif // SOCKET_H
