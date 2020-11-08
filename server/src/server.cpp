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
    
    // initialize fixed pool of memory
    pool nicu_pool = pool((MAX_CLIENT_COUNT * sizeof(client)), sizeof(client));
    nicu_pool.init();
    
    // initialize track of how many clients 
    int current_client_count = 0;
   
    // event driven development TO BE PROPERLY CODED WEEK 2 IN ORDER TO ENSURE CODE INTEGRATION STANDARDS
    /*
        bool is_good = 1;
        *client clients[50];
        while(is_good) {
            if(new_client_connected) {
                clients[current_client_count] = nicu_pool.allocate(sizeof(client));
                current_client_count++;
                
            }
            
            // first main error to check
            for(int i = 0; i < current_client_count; ++i) {
                if(&clients[i].is_oob) {
                    is_good = 0;
                    exit("Out of Bounds Error on Client %d", i);
                }
            }
            // second main error to check
            if(MAX_CLIENT_COUNT < client_current_count + 1) {
                is_good = 0;
                exit("Out of Bounds Error for the Pool");
            }
            
        }
        
        
        // when the code exits, the pool needs to be freed. Maybe this can be made into a helper function and put prior to the exit statements?
        for(int i = current_client_count; i >= 0; --i) {
            nicu_pool.free(clients[i]);
        }
    */
    
    
    return 0;
}
