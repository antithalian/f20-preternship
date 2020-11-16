# f20-preternship
Fall 2020 Notre Dame CSE 20312 Preternship Project    
GE Healthcare Team - John Sullivan, Jacob Larget, Jacob Nemec

## TO DO
- build out `make format` functionality
    - although that will probably only work on John's machine unless everyone else gets clang-format and -tidy
- finish Python dummy launcher
- make server more easily killable (aside from CTRL-C)
    
## Finished
- make server/pool compileable via makefile
- make `make clean` work correctly
    - needs to actually clean things up, for starters
- abandoned smalloc :(
- tested pool.hpp
    - resolved segfault bug in pool/slinked_list
- learned about zeromq
- implemented zeromq in server and client (dummy device)
- implemented logic layers on both sides
    - including pool storage
