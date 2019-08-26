CXX = g++
CXXFLAGS = -g -Wfatal-errors -lstdc++ -std=c++11
OBJFLAGS = -c

SSOURCES = server.cpp Command.cpp CommandList.cpp helpers.cpp
CSOURCES = client.cpp helpers.cpp

SOBJECTS = $(SSOURCES:.cpp=.o)
COBJECTS = $(CSOURCES:.cpp=.o)

SERVER = server
CLIENT = client

%.o: %.cpp
	$(CXX) $(OBJFLAGS) $(CXXFLAGS) -o $@ $<

all: $(SERVER) $(CLIENT)
	@echo Compiling server and client
    
$(SERVER): $(SOBJECTS)
	$(CXX) $(CXXFLAGS) $(SSOURCES) -o $(SERVER)

$(CLIENT): $(COBJECTS)
	$(CXX) $(CXXFLAGS) $(CSOURCES) -o $(CLIENT)

clean:
	-rm -f *.o
	-rm -f server
	-rm -f client
