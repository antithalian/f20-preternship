// dummy.cpp
// dummy NICU baby warmer

// stdlib includes
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>

// custom includes
#include "../../shared/msg_util.hpp"
#include "../include/dummy.hpp"
#include <zmqpp/zmqpp.hpp>


// MAGIC NUMBERS
// endpoint for zmq comms
const std::string ENDPOINT = "tcp://127.0.0.1:55555";

int main(int argc, char* argv[]) {

    // read in arguments
    // assume python program gave the correct stuff
    // serial
    unsigned int serial = (unsigned int) atoi(argv[0]);
    // amplitude
    double ampl;
    // phase shift
    double shif;
    // time
    double time;
    // oob gen?
    bool oob_gen;

    // create identifier from serial
    std::string ident = create_ident(serial);
  
    // set up zmq client
    // create context
    zmqpp::context context;
    // generate socket
    zmqpp::socket_type type = zmqpp::socket_type::request;
    zmqpp::socket socket (context, type);
    // connect to socket
    socket.connect(ENDPOINT);

    // loop sentinel
    bool die = false;
    // active loop
    while (!die) {



    }

}

// creates an identifier for a client given a serial number for the warmer
std::string create_ident(unsigned int serial) {

    std::string ret = "CLIENT_WARMER_" + std::to_string(serial);
    return ret;
}
double get_temp(double, double, double) {

}

// 97.9-100.4F typical