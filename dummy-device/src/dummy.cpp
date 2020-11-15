// dummy.cpp
// dummy NICU baby warmer

// stdlib includes
#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

// custom includes
#include "../../shared/msg_util.hpp"
#include "../include/dummy.hpp"
#include <zmqpp/zmqpp.hpp>

// IO defines
#define COUT std::cout
#define ENDL std::endl

// MAGIC NUMBERS
// endpoint for zmq comms
const std::string ENDPOINT = "tcp://127.0.0.1:55555";

int main(int argc, char* argv[]) {

    // read in arguments
    // assume python program gave the correct stuff
    unsigned int serial;
    double ampl, shif;
    bool oob_gen;
    if (argc == 4) {
        // serial
        serial = (unsigned int) atoi(argv[0]);
        // amplitude
        ampl = strtod(argv[1], NULL);
        // phase shift
        shif = strtod(argv[2], NULL);
        // oob gen?
        oob_gen = strtod(argv[3], NULL);
    }
    else {
        return 1;
    }
    // time
    double time = 0;

    // create identifier from serial
    std::string ident = create_ident(serial);

    // set up payload structs to reuse
    payload self = payload("TEMP", ident, 0.0);
    payload recvd = payload("COMM", "SERVER_WARMER_00", 0.0);
  
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

        // send current state to server
        // BUILD THIS OUT

        // wait for server response
        zmqpp::message recv_msg;
        socket.receive(recv_msg, zmqpp::socket::normal);
        // put received contents into string
        std::string recv_str;
        recv_msg >> recv_str; // contents of payload from client

        // reconstruct payload
        recvd.type = recv_str.substr(0, 4);
        recvd.identifier = recv_str.substr(4, 16);
        recvd.temperature = std::stod(recv_str.substr(20));

        // react to whatever the server said to do
        // BUILD THIS OUT

        // sleep for a bit
        std::chrono::milliseconds wait(1000); // wait 1s
        std::this_thread::sleep_for(wait);
        // increment the time
        time++;
    }

    // if we make it to here, shut down context and return
    socket.disconnect(ENDPOINT);
    socket.close();
    context.terminate();
    return 0;
}

// creates an identifier for a client given a serial number for the warmer
std::string create_ident(unsigned int serial) {

    std::string ret = "CLIENT_WARMER_" + std::to_string(serial);
    return ret;
}
double get_temp(double time, double ampl, double shif, bool go_oob) {
    // BUILD THIS OUT
}

// 97.9-100.4F typical