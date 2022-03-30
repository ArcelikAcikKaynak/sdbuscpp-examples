#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    // Create D-Bus connection to the system bus and requests name on it.
    const char* serviceName = "org.sdbuscpp.concatenator";
    auto connection = sdbus::createSystemBusConnection(serviceName);

    // Create concatenator D-Bus object.
    const char* objectPath = "/org/sdbuscpp/concatenator";
    auto concatenator = sdbus::createObject(*connection, objectPath);
    
    auto concatenate = [&concatenator](const std::vector<int> numbers, const std::string& separator)
    {
        // Return error if there are no numbers in the collection
        if (numbers.empty())
            throw sdbus::Error("org.sdbuscpp.Concatenator.Error", "No numbers provided");

        std::string result;
        for (auto number : numbers)
        {
            result += (result.empty() ? std::string() : separator) + std::to_string(number);
        }

        // Emit 'concatenated' signal
        const char* interfaceName = "org.sdbuscpp.Concatenator";
        concatenator->emitSignal("concatenated").onInterface(interfaceName).withArguments(result);

        return result;
    };

    // Register D-Bus methods and signals on the concatenator object, and exports the object.
    const char* interfaceName = "org.sdbuscpp.Concatenator";
    concatenator->registerMethod("concatenate").onInterface(interfaceName).implementedAs(std::move(concatenate));
    concatenator->registerSignal("concatenated").onInterface(interfaceName).withParameters<std::string>();
    concatenator->finishRegistration();

    // Run the loop on the connection.
    std::cout << "Entering event loop" << std::endl;
    connection->enterEventLoop();
}