#ifndef X4_SOCKETS_SERVER_HEADER_GUARD
#   define X4_SOCKETS_SERVER_HEADER_GUARD

#   include "common.hpp"

namespace x4::net {
    // TODO: make parameterized template class to make use of several transports,
    // e.g. TCP, UDP, TLS
    class Server {
        public:
            Server(Port port)
                : socket_handle{ ::socket(AF_INET, SOCK_STREAM, 0) }
            {
                struct sockaddr_in server_addr = { 0 };
                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = INADDR_ANY;
                server_addr.sin_port = ::htons(port);
                if (0 > ::bind(this->socket_handle,
                               reinterpret_cast<struct sockaddr*>(&server_addr),
                               sizeof(server_addr)))
                { throw 1; }
                ::listen(this->socket_handle, 10);
            }

            ~Server(void) noexcept
            { ::close(this->socket_handle); }

            SocketHandle
            accept(void) noexcept
            {
                struct sockaddr_in client_addr = { 0 };
                socklen_t client_addr_len{ sizeof(client_addr) };
                return ::accept(this->socket_handle,
                                reinterpret_cast<struct sockaddr*>(&client_addr),
                                &client_addr_len);
            }

        private:
            SocketHandle socket_handle;
    }; /// !Server
} /// !x4::net

#endif /// !X4_SOCKETS_SERVER_HEADER_GUARD
