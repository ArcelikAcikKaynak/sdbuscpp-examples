#ifndef CONCATENATOR_CLIENT_H_
#define CONCATENATOR_CLIENT_H_

#include <sdbus-c++/sdbus-c++.h>
#include "concatenator_client_glue.h"
#include <iostream>

class ConcatenatorProxy : public sdbus::ProxyInterfaces<org::sdbuscpp::Concatenator_proxy /*, more proxy classes if there are more interfaces*/>
{
public:
    ConcatenatorProxy(std::string destination, std::string objectPath)
        : ProxyInterfaces(std::move(destination), std::move(objectPath))
    {
        registerProxy();
    }

    ~ConcatenatorProxy()
    {
        unregisterProxy();
    }

protected:
    void onConcatenated(const std::string& concatenatedString) override
    {
        std::cout << "Received signal with concatenated string " << concatenatedString << std::endl;
    }
};

#endif // CONCATENATOR_CLIENT_H_