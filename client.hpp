#ifndef X4_SOCKETS_CLIENT_HEADER_GUARD
#   define X4_SOCKETS_CLIENT_HEADER_GUARD

#   include "common.hpp"

namespace x4::net {
    // TODO: make parameterized template class to make use of several transports,
    // e.g. TCP, UDP, TLS
    class Client {
        public:
            Client(SocketHandle const& sh) noexcept
                : socket_handle{ sh }
            {}

            Client(Host host, Port port)
                : socket_handle{ ::socket(AF_INET, SOCK_STREAM, 0) }
            {
                auto const* server{ ::gethostbyname(host.c_str()) };
                struct sockaddr_in server_addr = { 0 };
                server_addr.sin_family = AF_INET;
                server_addr.sin_port = ::htons(port);
                std::memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
                if (0 > ::connect(this->socket_handle,
                                  reinterpret_cast<struct sockaddr*>(&server_addr),
                                  sizeof server_addr))
                { throw 2; }
            }
    
            operator SocketHandle&(void) { return this->socket_handle; }

            template <std::size_t S>
            auto
            receive(std::array<unsigned char, S>& in, bool bufferize = false)
            { return ::recv(this->socket_handle, in.data(), S - 1, 0); }

            void
            send(std::string message)
            { ::send(this->socket_handle, message.data(), message.size(), 0); } 
    
            ~Client(void) noexcept
            { ::close(this->socket_handle); }
    
        private:
            SocketHandle socket_handle;
    }; /// !Client
} /// !x4::net

#endif /// !X4_SOCKETS_CLIENT_HEADER_GUARD
