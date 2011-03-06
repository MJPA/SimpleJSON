# Change to whatever your C++ compiler is
CC=g++

# Compile settings
CFLAGS=-c -Wall
LFLAGS=-lm

# Source files
SOURCES=src/JSON.cpp src/JSONValue.cpp src/demo/nix-main.cpp src/demo/example.cpp src/demo/testcases.cpp
HEADERS=src/JSON.h src/JSONValue.h
OBJECTS=$(SOURCES:src/%.cpp=obj/%.o)

# Output
EXECUTABLE=JSONDemo

all:	$(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE):	$(OBJECTS) 
		$(CC) $(LFLAGS) $(OBJECTS) -o $@

obj/%.o:	src/%.cpp $(HEADERS)
		@test -d $(@D) || mkdir -p $(@D)
		$(CC) $(CFLAGS) $(@:obj/%.o=src/%.cpp) -o $@

clean:
		rm -f $(OBJECTS) $(EXECUTABLE)

