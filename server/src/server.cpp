// server.cpp
// defines and implements functionality for a NICU baby warmer C&C server

// stdlib includes
#include <iostream>

// custom includes
#include "../include/pool.hpp"


// MAGIC NUMBERS
// maximum number of clients allowed
#define MAX_CLIENT_COUNT 50

// client struct
// needs to be constant size for pool allocator to work right
struct client {

    // client identifier
    char ident[32];
    // client's current temp
    int curr_temp;
    // last 10 temps received from client
    int last_temps[10];
    // client's out-of-bounds state
    bool is_oob;
};

// test main
int main(void) {
    return 0;
}
