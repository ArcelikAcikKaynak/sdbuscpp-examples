#include "concatenator_client.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Create proxy object for the concatenator object on the server side
    const char* destinationName = "org.sdbuscpp.concatenator";
    const char* objectPath = "/org/sdbuscpp/concatenator";
    ConcatenatorProxy concatenatorProxy(destinationName, objectPath);

    std::vector<int> numbers = {1, 2, 3};
    std::string separator = ":";

    // Invoke concatenate with some numbers
    auto concatenatedString = concatenatorProxy.concatenate(numbers, separator);
    assert(concatenatedString == "1:2:3");

    // Invoke concatenate again, this time with no numbers and we shall get an error
    try
    {
        auto concatenatedString = concatenatorProxy.concatenate(std::vector<int>(), separator);
        assert(false);
    }
    catch(const sdbus::Error& e)
    {
        std::cerr << "Got concatenate error " << e.getName() << " with message " << e.getMessage() << std::endl;
    }

    // Give sufficient time to receive 'concatenated' signal from the first concatenate invocation
    sleep(1);

    return 0;
}