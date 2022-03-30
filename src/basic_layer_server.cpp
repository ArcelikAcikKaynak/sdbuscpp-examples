#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>

// Yeah, global variable is ugly, but this is just an example and we want to access
// the concatenator instance from within the concatenate method handler to be able
// to emit signals.
sdbus::IObject* g_concatenator{};

void concatenate(sdbus::MethodCall call)
{
    // Deserialize the collection of numbers from the message
    std::vector<int> numbers;
    call >> numbers;

    // Deserialize separator from the message
    std::string separator;
    call >> separator;

    // Return error if there are no numbers in the collection
    if (numbers.empty())
        throw sdbus::Error("org.sdbuscpp.Concatenator.Error", "No numbers provided");

    std::string result;
    for (auto number : numbers)
    {
        result += (result.empty() ? std::string() : separator) + std::to_string(number);
    }

    // Serialize resulting string to the reply and send the reply to the caller
    auto reply = call.createReply();
    reply << result;
    reply.send();

    // Emit 'concatenated' signal
    const char* interfaceName = "org.sdbuscpp.Concatenator";
    auto signal = g_concatenator->createSignal(interfaceName, "concatenated");
    signal << result;
    g_concatenator->emitSignal(signal);
}

int main(int argc, char *argv[])
{
    // Create D-Bus connection to the system bus and requests name on it.
    const char* serviceName = "org.sdbuscpp.concatenator";
    auto connection = sdbus::createSystemBusConnection(serviceName);

    // Create concatenator D-Bus object.
    const char* objectPath = "/org/sdbuscpp/concatenator";
    auto concatenator = sdbus::createObject(*connection, objectPath);

    g_concatenator = concatenator.get();

    // Register D-Bus methods and signals on the concatenator object, and exports the object.
    const char* interfaceName = "org.sdbuscpp.Concatenator";
    concatenator->registerMethod(interfaceName, "concatenate", "ais", "s", &concatenate);
    concatenator->registerSignal(interfaceName, "concatenated", "s");
    concatenator->finishRegistration();

    // Run the I/O event loop on the bus connection.
    std::cout << "Entering event loop" << std::endl;
    connection->enterEventLoop();
}