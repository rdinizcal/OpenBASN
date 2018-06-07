#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>
#include <deque>
#include <vector>
#include <mutex>
#include <atomic>
#include <string.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptor.h>
#include <opendavinci/odcore/io/tcp/TCPFactory.h>
#include <opendavinci/odcore/io/ConnectionListener.h>
#include <opendavinci/odcore/io/StringListener.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptorListener.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

class TCPReceiveBytes : 
    public odcore::io::ConnectionListener,
    public odcore::io::StringListener,
    public odcore::io::tcp::TCPAcceptorListener {

    private:    
    std::atomic_bool should_run;
    std::shared_ptr<odcore::io::tcp::TCPConnection> this_connection;
    std::shared_ptr<odcore::io::tcp::TCPAcceptor> tcpacceptor;

    virtual void nextString(const std::string &s);

    void push(std::string);

    virtual void onNewConnection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection);

    virtual void handleConnectionError();

    public:

    std::string get_package();
    void stop_connection();
    void initialize();
    
};

