#include "client.hpp"

#include <iostream>

#define debugLog(msg) do{ std::cout << msg << '\n'; }while(false)

int
main(int argc, char* argv[])
{
    x4::net::Client client{ "0.0.0.0", 7070 };
    debugLog("to send");

    for (std::string buf; std::getline(std::cin, buf); )
    {
        client.send(buf);
    }
}

