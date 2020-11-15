// msg_util.hpp
// defines some useful bits for sending messages between server and dummy devices

#ifndef MSG_UTIL_H
#define MSG_UTIL_H

// includes
#include <string>

// message payload struct
struct payload {

    // 4 character message type
    // expected types are KILL, TEMP, COMM
    std::string type;
    // 16 character sender identifier
    std::string identifier;
    // double temperature - depending on type this is either a target or current temp
    double temperature;

    // constructor
    payload(const std::string in_type, const std::string in_ident, double in_temp) : 
        type(in_type), identifier(in_ident), temperature(in_temp) {}

    // serialize
    // convert attributes into one string
    std::string serialize() {
        return (type + identifier + std::to_string(temperature));
    }
};

// originally meant to include send and receive functions
// however, code clarity seemed to go down when not just directly using zmqpp

#endif