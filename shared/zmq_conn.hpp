// zmq_conn.hpp
// defines an interface for communication between server and dummy devices

// includes
#include <zmq.hpp>

// MAGIC NUMBERS
// size of a single message
#define MSG_SIZE 0xBEEF // TODO - get an actual number

// message struct
struct message {

    // 4 character message type
    // expected types are KILL, TEMP, COMM
    const char* typ[4];
    // double temperature - depending on type this is either a target or current temp
    double temperature;
    // size of struct
    unsigned int size = sizeof(typ) + sizeof(temperature);

    // constructor
    message(const char* intype[4], double intemp) : typ(intype), temperature(intemp) {}

    // serialize
    // serializes all struct members into a caller-provided buffer
    void serialize(char* &buffer) {

        // 
    }

};

// zmq send
bool zmq_send(zmq::socket_t sock, const char* send_buffer) {

    // sends a zmq message with the contents of the const char * send_buffer that was passed in
    // returns true if good send

}

// zmq receive
bool zmq_receive(zmq::socket_t sock, char* &recv_buffer) {

    // receives a zmq message from the socket_t sock and places it into recv_buffer
    // returns true if good receive

}