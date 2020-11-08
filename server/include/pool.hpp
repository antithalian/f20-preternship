// pool.hpp
// declares functions and structs required pool.cpp

#ifndef POOL_H
#define POOL_H

// stdlib includes
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <cstdint>

// custom includes
#include "../../shared/slinked_list.hpp"

class pool {

    private:

        // total size of pool in bytes
        std::size_t total_size;
        // size of a single chunk in bytes
        std::size_t chunk_size;

        // keep track of current and peak size because why not
        std::size_t peak_size, curr_size;

        // memory region start pointer
        void* start_ptr = NULL;

        // free list
        slinked_list<std::size_t> free_list;

    public:

        // default constructor
        // total size MUST be a multiple of chunk size
        // proper usage is to call "pool((n * sizeof(data)), sizeof(data))"
        pool(const std::size_t intotal_size, const std::size_t inchunk_size) : 
            total_size(intotal_size), 
            chunk_size(inchunk_size), 
            peak_size(0), 
            curr_size(0) {}

        // destructor
        ~pool() {
            // just free the whole chunk we allocated
            free(start_ptr);
        }

        // initialize
        // call after calling constructor
        void init() {

            // allocate full amount of memory required
            start_ptr = malloc(total_size);

            // figure out number of chunks
            const std::size_t chunk_count = total_size / chunk_size;

            // create linked list with all free positions
            for (std::size_t i = 0; i < chunk_count; i++) {

                // determine address for start of chunk
                std::size_t addr = (std::size_t) ((std::size_t) start_ptr + (i * chunk_size));

                // push onto free list
                free_list.push_front(addr);
            }
        }

        // allocate
        void* alloc(const std::size_t size) {
            
            // if size is not correct, return NULL
            // on the caller to check that they actually got good memory back
            if (size != chunk_size) {
                return NULL;
            }

            // get next free position from free list
            // then remove it from free list
            std::size_t free_pos = free_list.front();
            free_list.pop_front();

            // update amount of memory used
            curr_size += chunk_size;
            peak_size = std::max(peak_size, curr_size);

            // return the retrieved address as a void pointer
            return (void*) free_pos;
        }

        // free
        void free(void* pointer) {
            
            // drop the current used size
            curr_size -= chunk_size;

            // push pointer onto freelist
            free_list.push_front((std::size_t) pointer);
        }

        // simple getters for internal data
        // get total size
        std::size_t get_total_size() {
            return total_size;
        }

        // get chunk size
        std::size_t get_chunk_size() {
            return chunk_size;
        }

        // get peak size
        std::size_t get_peak_size() {
            return peak_size;
        }

        // get current size
        std::size_t get_curr_size() {
            return curr_size;
        }
};

#endif