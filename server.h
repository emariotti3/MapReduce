#ifndef SERVER_H
#define SERVER_H

#include "server_reducer.h"
#include "server_city_info_receiver.h"
#include "server_client_acceptor.h"

#define SERVER_MODE "server"

class Server{
    public:
        Server(std::string port);
        int main (int argc, char *argv[]);
        void run();
        virtual ~Server();
    protected:
    private:
        std::string port;
        std::string hostname;
        int max_threads;
        std::map<int, Reducer*> reducers;
};


int main(int argc, char *argv[]){
    std::stringstream stream(*argv);
    std::string mode = "";
	stream >> mode;

    const std::string server_mode = SERVER_MODE;
    bool mode_is_server = server_mode.compare(mode);

    if (!mode_is_server){
        //exception!
    }

    std::string port = "";
    stream >> port;
    Server s(port);
    s.run();
    return 0;
}


#endif // SERVER_H
