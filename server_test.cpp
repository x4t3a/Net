#include "server.hpp"
#include "client.hpp"

#include <algorithm>
#include <iostream>
#include <thread>

#define debugLog(msg) do{ std::cout << msg << '\n'; }while(false)

namespace {
    const std::string ex{ "exit" };
}

void
serveClient(x4::net::Client client)
{
    for (std::array<unsigned char, 128> in{ '\0' }; client.receive(in); )
    {
        std::cout << in.data() << '\n';
        if (std::includes(std::begin(in), std::end(in),
                          std::begin(ex), std::end(ex)))
        { break; }
        in = { '\0' };
    }
    debugLog("serveClient exit");
}

int
main(int argc, char* argv[])
{
    x4::net::Server server{ 7070 };
    debugLog("started");

    for (volatile bool run{ true }; run; )
    {
        debugLog("waiting for a client");
        std::thread client{ serveClient, server.accept() };
        client.detach();
    }
}

