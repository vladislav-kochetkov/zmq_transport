#ifndef I_TRANSPORT_H_
#define I_TRANSPORT_H_

#include <string>

class i_transport {
public:
        virtual void connect(const std::string&) = 0;
        virtual bool is_connected() const = 0;
        virtual void disconnect() = 0;
        virtual void send(char*, size_t) = 0;
        virtual void configure(const std::string&, const std::string&) = 0;
        virtual void receive(char*, size_t&) = 0;
        virtual ~i_transport() {}
};

#endif /* I_TRANSPORT_H_ */
