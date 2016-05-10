#ifndef SOCKETINFO_H
#define SOCKETINFO_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class SocketInfo{
    public:
        SocketInfo();
        void generateInfo(char hostname[], char port[], bool flags);
        virtual ~SocketInfo();
    private:
        struct addrinfo hints;
        struct addrinfo *addr;
        friend class Socket;
};

#endif // SOCKETINFO_H
