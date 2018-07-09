#include "bsn/communication/TCPSend.hpp"

using namespace std;
using namespace odcore;
using namespace odcore::io::tcp;

TCPSend::TCPSend() {}

TCPSend::TCPSend(std::string this_ip, int this_port) {
    port = this_port;
    ip = this_ip;
    is_connected = false;
}

bool TCPSend::connect(){
    try{                
        std::shared_ptr<TCPConnection> connection(TCPFactory::createTCPConnectionTo(ip, port));                
        connection->setRaw(true);        
        this_connection = connection;                                
        cout << "Sender connected on " << get_port() << endl;
        is_connected = true;
        return true;
    }
    catch(string &exception) {
        cout << "Sender couldn't connect on " << get_port() << '(' << exception << ')' << endl;
        is_connected = false;
        return false;
    }   
}
int TCPSend::get_port() {
    return port;
}

void TCPSend::disconnect() {
    // Desaloca o ponteiro pra conexão
    this_connection.reset();
}

void TCPSend::send(string package){    
    if(is_connected){
        try {
            // Adiciona caracter separador
            package += '*';
            this_connection->send(package);        
        }
        catch(string &exception) {
            cerr << "Data could not be sent: " << exception << endl;
        }
    }
}

