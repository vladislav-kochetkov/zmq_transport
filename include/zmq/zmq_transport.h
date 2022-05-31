#ifndef ZMQ_TRANSPORT_H
#define ZMQ_TRANSPORT_H

#include <string>
#include <zmq.h>
#include <vector>
#include <stdint.h>

typedef std::vector<uint8_t> byte_vector;

#include "i_transport.h"

class zmq_transport : public i_transport
{
private:
    void* _context;
    void* _socket;
    int _socket_type;
    bool _is_connected;

public:
    zmq_transport();

    virtual void connect(const std::string&);
    virtual void disconnect();
    virtual void send(char*, size_t);
    virtual void receive(char* buf, size_t& size);
    virtual void configure(const std::string&, const std::string&);
    virtual bool is_connected() const;
    virtual ~zmq_transport();
};

#endif // ZMQ_TRANSPORT_H
