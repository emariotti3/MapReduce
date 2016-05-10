#include "common_socket.h"
#include "common_system_error.h"
#include "common_socket_info.h"
#include <exception>
#include <string>

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#define MAXLEN_CONNECTION_QUEUE 10
#define INVALID_DESC -1
#define ERROR -1
#define OK 0
#define SIZE_RECEIVE 1
#define MSG_ERROR_CREATE "Cannot create socket! Invalid file descriptor!"
#define MSG_ERROR_LISTEN "socket_listen() operation invalid!"
#define MSG_ERROR_BIND "Cannot bind socket!"
#define MSG_ERROR_SEND "socket_send() operation invalid!"
#define MSG_ERROR_RECV "socket_receive() operation invalid!"
#define MSG_FD "File descriptor: "

Socket::Socket(char hostname[], char port[], bool set_flags):
hostname(hostname),
port(port),
set_flags(set_flags){
    this->sckt_info.generateInfo(this->hostname, this->port, this->set_flags);

	int new_fd = socket(this->sckt_info.addr->ai_family,
						this->sckt_info.addr->ai_socktype,
						this->sckt_info.addr->ai_protocol);

	if (new_fd == INVALID_DESC){
        std::string error(MSG_ERROR_CREATE);
		throw SystemError(error, __FILE__, __LINE__);
	}
 	this->fd = new_fd;
}

int Socket::getFileDescriptor(){
    return this->fd;
}

void Socket::socket_shutdown(int how_flag){
	shutdown(this->fd, how_flag);
}

void Socket::socket_bind(){
	try{
		int success = bind(this->fd,
						this->sckt_info.addr->ai_addr,
						this->sckt_info.addr->ai_addrlen);
		if (success != OK){
			std::stringstream file_desc;
			file_desc << this->fd;
			std::string error_desc(MSG_ERROR_BIND);
			error_desc.append(MSG_FD);
			error_desc.append(file_desc.str());
			throw SystemError(error_desc, __FILE__, __LINE__);
		}
	}catch(std::exception &e){
		std::string error_desc = MSG_ERROR_BIND;
		throw SystemError(error_desc, __FILE__, __LINE__);
	}
}

void Socket::setFileDescriptor(int new_fd){
    this->fd = new_fd;
}

void Socket::socket_listen(){
	int success = listen(this->fd, MAXLEN_CONNECTION_QUEUE);

    if (success != OK){
        std::stringstream file_desc;
        file_desc << this->fd;
        std::string error_desc(MSG_ERROR_LISTEN);
		error_desc.append(MSG_FD);
		error_desc.append(file_desc.str());
		throw SystemError(error_desc, __FILE__, __LINE__);
	}
}

void Socket::socket_accept(Socket &connection_socket){
	int new_fd;
	new_fd = accept(this->fd, NULL, NULL);

	if (new_fd != INVALID_DESC){
        connection_socket.setFileDescriptor(new_fd);
	}
}

bool Socket::socket_connect(){
	int success = connect(this->fd,
                            this->sckt_info.addr->ai_addr,
							this->sckt_info.addr->ai_addrlen);

	bool connection_list_ended = (this->sckt_info.addr == NULL);

	int fd = 0;
	while ( (!connection_list_ended) && (success == ERROR) ){
		this->sckt_info.addr = this->sckt_info.addr->ai_next;
		connection_list_ended = (this->sckt_info.addr == NULL);
		try{
			Socket s(this->hostname, this->port, this->set_flags);
			this->fd = s.getFileDescriptor();

			if ((!connection_list_ended) && (fd != INVALID_DESC)){
				success = connect(this->fd,
									this->sckt_info.addr->ai_addr,
									this->sckt_info.addr->ai_addrlen);
			}
		}catch(SystemError &e){
			success = ERROR;
		}
	}

    return (success != ERROR);
}

void Socket::socket_send(char *buffer, size_t size){
	size_t sent = 0;
	size_t total_sent = 0;

	while ((size - total_sent) != 0){
		sent = send(this->fd, buffer + total_sent, size - total_sent, MSG_NOSIGNAL);

		if (sent < 0){
			std::string error_desc = MSG_ERROR_SEND;
			error_desc += MSG_FD + this->fd;
            throw SystemError(error_desc, __FILE__, __LINE__);
		}

		total_sent += sent;
	}
}

void Socket::socket_receive(char *buffer, size_t size){
	size_t read = 0;
	size_t total_received = 0;
	char *pos = NULL;
	while ((size - total_received) != 0){
		pos = buffer + total_received;
		read = recv(this->fd, pos, size - total_received, MSG_NOSIGNAL);
		if (read < 0){
			std::string error_desc = MSG_ERROR_RECV;
			error_desc += MSG_FD + this->fd;
            throw SystemError(error_desc, __FILE__, __LINE__);
		}
		total_received += read;
	}
}

void Socket::socket_receive(char *buff, 
							size_t sz, 
							char *delim, 
							size_t sz_delim)
{
	size_t read = 0;
	size_t total = 0;
	char *pos = NULL;
	bool received_delim = false;
	bool continue_recv = (total < sz);
	while (continue_recv){
		pos = buff + total;
		try{
			read = recv(this->fd, pos, SIZE_RECEIVE, MSG_NOSIGNAL);
			if (read < 0){
				std::string error_desc = MSG_ERROR_RECV;
				error_desc += MSG_FD + this->fd;
				error_desc += strerror(errno);
				throw SystemError(error_desc, __FILE__, __LINE__);
			}
			total += read;
			//if (total >= sz_delim){	
				received_delim = (strncmp(delim, pos - sz_delim + 1, sz_delim) != 0);
			//}
			continue_recv = (received_delim) && (total < sz);
		}catch(std::exception &e){
			std::string error_desc = MSG_ERROR_RECV;
			error_desc += MSG_FD + this->fd;
			error_desc += strerror(errno);
			throw SystemError(error_desc, __FILE__, __LINE__);
		}
	}
}

Socket::~Socket(){
	close(this->fd);
}

