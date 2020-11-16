// killer.cpp
// sends a message to the server to have it kill everything

#include "../../shared/msg_util.hpp"
#include <iostream>
#include <string>
#include <zmqpp/zmqpp.hpp>

// MAGIC NUMBERS
// endpoint for zmq comms
const std::string ENDPOINT = "tcp://127.0.0.1:55555";

int main(void)
{
    // set up zmq client
    // create context
    zmqpp::context context;
    // generate socket
    zmqpp::socket_type type = zmqpp::socket_type::request;
    zmqpp::socket socket(context, type);
    // connect to socket
    socket.connect(ENDPOINT);

    // create killer payload
    payload killer = payload("KILL", "KILLER_KILLER_00", 0);

    // put killer string into killer message
    zmqpp::message kill_msg;
    kill_msg << killer.serialize();

    // send killer message with dont_wait
    socket.send(kill_msg, zmqpp::socket::dont_wait);

    return 0;
}