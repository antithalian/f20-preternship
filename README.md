# f20-preternship
Fall 2020 Notre Dame CSE 20312 Preternship Project    
GE Healthcare Team - John Sullivan, Jacob Larget, Jacob Nemec

## TO DO
- build out `make format` functionality
    - although that will probably only work on John's machine unless everyone else gets clang-format and -tidy
- try to debug smalloc issues
    - abandon that if we can't get it working
- further testing for pool.hpp
    - probably some bugs in the various casts going on and the free list implementation
- possibly add better error checking to pool.hpp
- read up on ZeroMQ
    - then add it to shared libs
    
## Finished
- make server/pool compileable via makefile
- make `make clean` work correctly
    - needs to actually clean things up, for starters
