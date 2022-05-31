/*
    This is free software; you can redistribute and/or modify it under the
    terms of the GNU Lesser General Licence as published by the Free Software
    Foundation. See the COPYING file for more information.
    
    This software is distributed WITHOUT ANY WARRANTY and without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "zmq/zmq_transport.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>


using namespace std;

zmq_transport::zmq_transport() :
        _socket(NULL),
        _socket_type(0),
        _is_connected(false)
{
    _context = zmq_ctx_new();
    if (!_context) {
        throw runtime_error("Unable to create 0MQ context");
    }
}

zmq_transport::~zmq_transport()
{
    disconnect();
    if (_context) {
        zmq_ctx_destroy(_context);
    }
}

void zmq_transport::connect(const std::string& endpoint)
{
    if (endpoint.empty()) {
        cout << "Endpoint is empty. ZMQ aborting..." << endl;
        return;
    }

    _socket = zmq_socket(_context, _socket_type);

    if (!_socket) {
        throw runtime_error("Unable to create PUB socket. Error: " + string(strerror(errno)));
    }

    if (_socket_type == ZMQ_PUB) {
        int rc = zmq_bind(_socket, endpoint.c_str());

        if (rc == -1) {
            throw runtime_error("Unable to bind to " + endpoint + " Error: " + string(strerror(errno)));
        }

        cout << "Listening: " << endpoint << endl;

    } else if (_socket_type == ZMQ_SUB) {
        int rc = zmq_connect(_socket, endpoint.c_str());

        if (rc == -1) {
            throw runtime_error("Unable to connect to " + endpoint + " Error: " + string(strerror(errno)));
        }

        cout << "Connected to: " << endpoint << endl;

        zmq_setsockopt(_socket, ZMQ_SUBSCRIBE, "", 0);
    }

    _is_connected = true;
}

bool zmq_transport::is_connected() const
{
    return _is_connected;
}

void zmq_transport::disconnect()
{
    _is_connected = false;
    if (_socket) {
        zmq_close(_socket);
    }
}

void zmq_transport::send(char* msg, size_t size)
{
    if (_socket) {
        int bytes = zmq_send(_socket, msg, size, ZMQ_DONTWAIT);
        if (bytes != size) {
            cout << "Message [" << msg << "] sent only " << bytes << " of " << size << " bytes";
        }
    }
}

void zmq_transport::receive(char* buf, size_t& size)
{
    size= zmq_recv(_socket, buf, 256, 0);
}

void zmq_transport::configure(const string & key, const string & value)
{
    if (key == "0MQ_SOCKET_TYPE") {
        if (value == "ZMQ_PUB") {
            _socket_type = ZMQ_PUB;
        } else if (value == "ZMQ_SUB") {
            _socket_type = ZMQ_SUB;
        } else {
            throw runtime_error("Unsupported socket type: " + value);
        }
    }
}


