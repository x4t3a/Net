#ifndef X4_SOCKETS_COMMON_HEADER_GUARD
#   define X4_SOCKETS_COMMON_HEADER_GUARD

extern "C" {
#   include <netdb.h>
#   include <netinet/in.h>
#   include <sys/socket.h>
#   include <sys/types.h>
#   include <unistd.h>
}

#   include <array>
#   include <cstddef>
#   include <cstring>
#   include <string>

namespace x4::net {
    using Host = std::string;
    using Port = int;
    using SocketHandle = int;
} /// !x4::net


#endif /// !X4_SOCKETS_COMMON_HEADER_GUARD
