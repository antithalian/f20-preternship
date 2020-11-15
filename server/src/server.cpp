// server.cpp
// defines and implements functionality for a NICU baby warmer C&C server

// stdlib includes
#include <iostream>
#include <queue>
#include <cstring>

// custom includes
#include "../include/pool.hpp"
#include "../../shared/msg_util.hpp"
#include <zmqpp/zmqpp.hpp>

// IO defines
#define COUT std::cout
#define ENDL std::endl

// MAGIC NUMBERS
// maximum number of clients allowed
#define MAX_CLIENT_COUNT 50
// endpoint for zmq comms
const std::string ENDPOINT = "tcp://127.0.0.1:55555";

// client struct
// needs to be constant size for pool allocator to work right
struct client {

    // client identifier
    char ident[17];
    // client's current temp
    double curr_temp;
    // last 10 temps received from client
    double last_temps[10];
    // client's out-of-bounds state
    bool is_oob;

    // constructor
    client(double in_curr_temp, bool in_is_oob) :
        curr_temp(in_curr_temp), is_oob(in_is_oob) {}

    // set identifier
    // returns true if successful, false if not
    bool set_ident(const std::string id) {

        // check that id is correct length (16 chars)
        if (id.length() != 16) {
            return false;
        }

        // copy contents of id into ident
        strcpy(ident, id.c_str());
        return true;
    }

    // update temps
    // put input temp at front of last temps and shift everything else
    void update_temps(double new_temp) {

        // add every element onto queue
        std::queue<double> holds;
        for (int i = 0; i < 10; i++) {
            holds.push(last_temps[i]);
        }

        // place new temp in both required locations
        curr_temp = new_temp;
        last_temps[0] = new_temp;

        // iterate through and put other temps back
        for (int i = 1; i < 10; i++) {
            last_temps[i] = holds.front();
            holds.pop();
        }
    }

};

// main
int main(void) {
    
    COUT << "--------------------" << ENDL << "Server startup:" << ENDL;

    // initialize fixed pool of memory
    pool nicu_pool = pool((MAX_CLIENT_COUNT * sizeof(client)), sizeof(client));
    nicu_pool.init();
    COUT << "client pool initialization - complete" << ENDL;
    
    // initialize var to keep track of how many clients are active
    int current_client_count = 0;

    // set up zmq server
    // create context
    zmqpp::context context;
    COUT << "zeromq context initialization - complete" << ENDL;
    // generate socket
    zmqpp::socket_type type = zmqpp::socket_type::reply;
    zmqpp::socket socket (context, type);
    // bind to socket
    socket.bind(ENDPOINT); // ENDPOINT defined in MAGIC up top
    COUT << "zeromq socket bound to endpoint - " << ENDPOINT << ENDL;

    // main active loop
    COUT << "entering main loop..." << ENDL << "--------------------" << ENDL;
    while (true) { // update this to kill itself on something...

        current_client_count++;
        break;

    }

    return 0;
}
