// server.cpp
// defines and implements functionality for a NICU baby warmer C&C server

// stdlib includes
#include <iostream>
#include <queue>

// custom includes
#include "../include/pool.hpp"
#include "../../shared/msg_util.hpp"


// MAGIC NUMBERS
// maximum number of clients allowed
#define MAX_CLIENT_COUNT 50
// endpoint for zmq comms
const std::string endpoint = "tcp://127.0.0.1:55555";

// client struct
// needs to be constant size for pool allocator to work right
struct client {

    // client identifier
    char ident[16];
    // client's current temp
    double curr_temp;
    // last 10 temps received from client
    double last_temps[10];
    // client's out-of-bounds state
    bool is_oob;

    // constructor
    client(double in_curr_temp, bool in_is_oob) :
        ident({'.'}), curr_temp(in_curr_temp), last_temps({0}) is_oob(in_is_oob) {}

    // set identifier
    // returns true if successful, false if not
    bool set_ident(const std::string id) {

        // check that id is correct length (16 chars)
        if (id.length() != 16) {
            return false;
        }

        // iterate through and set everything
        for (int i = 0; i < 16; i++) {
            ident[i] = id[i];
        }

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

// main server loop
int main(void) {
    
    // initialize fixed pool of memory
    pool nicu_pool = pool((MAX_CLIENT_COUNT * sizeof(client)), sizeof(client));
    nicu_pool.init();
    
    // initialize var to keep track of how many clients are active
    int current_client_count = 0;

    // set up zmq server
    // create context
    zmq::context_t ctx;
    // bind to addr and port
    


    // shut down everything
    // send message to all clients telling them to die

    // shut down zmq context
    ctx.shutdown();

    return 0;
}
