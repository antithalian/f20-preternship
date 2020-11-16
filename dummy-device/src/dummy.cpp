// dummy.cpp
// dummy NICU baby warmer

// stdlib includes
#include <cmath>
#include <ctime>
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
    if (argc == 5) {
        // serial
        serial = (unsigned int) atoi(argv[1]);
        // amplitude
        ampl = strtod(argv[2], NULL);
        // phase shift
        shif = strtod(argv[3], NULL);
        // oob gen
        oob_gen = (strcmp(argv[4], "true")) ? true : false;
    }
    else {
        return 1;
    }
    // time
    double time = 0;
    // target temp
    double target = 99.15;

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

    // active loop
    while (true) {

        // get and set current temperature based on parameters
        double curr_temp = get_temp(time, ampl, shif, oob_gen);
        self.temperature = curr_temp;
        // create a zmq message and put the payload into it
        zmqpp::message send_msg;
        send_msg << self.serialize();
        // send current state to server
        socket.send(send_msg, zmqpp::socket::normal);

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
        if (recvd.type == "COMM") {

            // if temp is not zero, adjust
            if (recvd.temperature != 0) {
                // obv irl we'd have to send a command to an actual heater
                target = recvd.temperature;
                oob_gen = false;
            }
        }
        // if not comm, it'll be kill, so die
        else {
            break;
        }

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

    std::string ret;
    if (serial < 10) {
        ret = "CLIENT_WARMER_0" + std::to_string(serial);
    }
    else {
        ret = "CLIENT_WARMER_" + std::to_string(serial);
    }
    return ret;
}
double get_temp(double time, double ampl, double shif, bool go_oob) {

    // calculate correct temperature for now time
    double freq = 0.5;
    double val = ampl * sin((freq * time) + shif);

    // if oob gen is set, take a chance at having it actually go oob
    if (go_oob) {
        srand((unsigned int) std::time(NULL));
        unsigned int res = rand() % 100;
        // have it maybe go oob if rand() was above 50
        if (res > 50) {
            if (val > 1.25) {
                return 99.15 + val + 2.5;
            }
            else {
                return 99.15 + val - 2.5;
            }
        }
    }

    return 99.15 + val;
}

// 97.9-100.4F typical