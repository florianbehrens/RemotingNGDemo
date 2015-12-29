#include <iostream>
#include <vector>

#include <Poco/Util/ServerApplication.h>
#include <Poco/RemotingNG/TCP/Listener.h>
#include <Poco/RemotingNG/TCP/TransportFactory.h>
#include <Poco/RemotingNG/ORB.h>

#include "ParameterServer.h"
#include "ParameterServerServerHelper.h"
#include "ParameterServerClientHelper.h"

class ServerApplication : public Poco::Util::ServerApplication
{
    int main(const std::vector<std::string>& args)
    {
        // 1. Create and register TCP listener.
        std::string listener = Poco::RemotingNG::ORB::instance().registerListener(
            new Poco::RemotingNG::TCP::Listener("localhost:9999")
        );

        // 2. Create the service object.
        Poco::SharedPtr<ParameterServer> pParameterServer = new ParameterServer;

        // 3. Register service object with ORB.
        std::string uri = ParameterServerServerHelper::registerObject(pParameterServer, "TheParameterServer", listener);
        std::cout << "ParameterServer URI is: " << uri << std::endl;

        // Start client
        try
        {
            // Register TCP transport.
            Poco::RemotingNG::TCP::TransportFactory::registerFactory();

            // Get proxy for remote ParameterServer.
            std::string uri("remoting.tcp://localhost:9999/tcp/ParameterServer/TheParameterServer");
            IParameterServer::Ptr pParameterServer = ParameterServerClientHelper::find(uri);

            // Invoke methods on remote object.
            std::string retval = pParameterServer->get_string("bla");
            std::cout << "Value: " << retval << std::endl;
        }
        catch (Poco::Exception& exc)
        {
            std::cerr << exc.displayText() << std::endl;
            return 1;
        }

        // Wait for CTRL-C or kill.
        waitForTerminationRequest();

        // Stop the remoting machinery.
        Poco::RemotingNG::ORB::instance().shutdown();

        return Application::EXIT_OK;
    }
};

POCO_SERVER_MAIN(ServerApplication)
