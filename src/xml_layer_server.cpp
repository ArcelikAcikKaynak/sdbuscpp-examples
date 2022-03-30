#include "concatenator_server.h"
#include <iostream>

int main(int argc, char *argv[])
{
    // Create D-Bus connection to the system bus and requests name on it.
    const char* serviceName = "org.sdbuscpp.concatenator";
    auto connection = sdbus::createSystemBusConnection(serviceName);

    // Create concatenator D-Bus object.
    const char* objectPath = "/org/sdbuscpp/concatenator";
    Concatenator concatenator(*connection, objectPath);

    // Run the loop on the connection.
    std::cout << "Entering event loop" << std::endl;
    connection->enterEventLoop();
}