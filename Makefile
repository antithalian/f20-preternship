# Preternship Project Makefile

# g++
PP := g++

# production quality compilation flags
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror 
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)
LINKFLAGS := -lzmq -lzmqpp

# project folders
DUMMY := dummy-device
SERVER := server

# subproject folders
INC := include
SRC := src
OBJ := obj
EXE := exe

# make server
ServerObjs := $(SERVER)/$(OBJ)/server.o

server: $(ServerObjs)
	$(PP) $(CXXFLAGS) $(LINKFLAGS) -o $(SERVER)/$(EXE)/server $(ServerObjs)

$(SERVER)/$(OBJ)/server.o: $(SERVER)/$(SRC)/server.cpp
	$(PP) $(CXXFLAGS) -c $(SERVER)/$(SRC)/server.cpp -o $@

# make dummy-device
DummyObjs := $(DUMMY)/$(OBJ)/dummy.o

dummy: $(DummyObjs)
	$(PP) $(CXXFLAGS) $(LINKFLAGS) -o $(DUMMY)/$(EXE)/dummy $(DummyObjs)

$(DUMMY)/$(OBJ)/dummy.o: $(DUMMY)/$(SRC)/dummy.cpp
	$(PP) $(CXXFLAGS) -c $(DUMMY)/$(SRC)/dummy.cpp -o $@

# make killer
KillerObjs := $(DUMMY)/$(OBJ)/killer.o

killer: $(KillerObjs)
	$(PP) $(CXXFLAGS) $(LINKFLAGS) -o $(DUMMY)/$(EXE)/killer $(KillerObjs)

$(DUMMY)/$(OBJ)/killer.o: $(DUMMY)/$(SRC)/killer.cpp
	$(PP) $(CXXFLAGS) -c $(DUMMY)/$(SRC)/killer.cpp -o $@

# make format
# requires that clang-tidy and clang-format be installed
# make format:
# add recursive find and format?

# make all
all: server dummy killer

# make clean
# separately cleans dummy and server objects and executables
clean:
	rm -rf $(SERVER)/$(OBJ)/* $(SERVER)/$(EXE)/* 
	rm -rf $(DUMMY)/$(OBJ)/* $(DUMMY)/$(EXE)/*

# full g++ args
# g++ -m64 -std=c++11 -Weffc++ -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lzmq -lzmqpp
