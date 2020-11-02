# Preternship Project Makefile

# g++
PP := g++

# production quality compilation flags
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror 
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# project folders
DUMMY := dummy-device
SERVER := server

# subproject folders
INC := include
SRC := src
OBJ := obj
EXE := exe

# make server
ServerObjs := $(SERVER)/$(OBJ)/server

server: $(ServerObjs)
	$(PP) $(CXXFLAGS) -o $(SERVER)/$(EXE)/SorDLLTest $(ServerObjs)

$(SERVER)/$(OBJ)/server.o: $(SERVER)/$(SRC)/server.cpp
	$(PP) $(CXXFLAGS) -c $(SERVER)/$(SRC)/server.cpp -o $@

# make dummy-device
DummyObjs := $(DUMMY)/$(OBJ)/dummy-device.o

dummy-device: $(DummyObjs)
	$(PP) $(CXXFLAGS) -o $(DUMMY)/$(EXE)/dummy-device $(DummyObjs)

$(DUMMY)/$(OBJ)/dummy-device.o: $(DUMMY)/$(SRC)/dummy-device.cpp
	$(PP) $(CXXFLAGS) -c $(DUMMY)/$(SRC)/dummy-device.cpp -o $@

# make format
# make format:
# add recursive find and format?

# make all
all: check server dummy-device

# make clean
clean :
	rm -rf *.o $(OBJ)/* $(EXE)/*

# full g++ args
# g++ -m64 -std=c++11 -Weffc++ -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror