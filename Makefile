CC = g++
CFLAGS = -g -Wfatal-errors -lstdc++ -std=c++11

SSOURCES = server.cpp Command.cpp 
CSOURCES = client.cpp

SOBJECTS = server.o Command.o
COBJECTS = ${CSOURCES:.cpp=.o}

SERVER = server
CLIENT = client

all: ${SERVER} ${CLIENT}
	@echo Compiling server and client
    
${SERVER}: ${SOBJECTS}
	${CC} ${CFLAGS} ${SSOURCES} -o ${SERVER}

${CLIENT}: ${COBJECTS}
	${CC} ${CFLAGS} ${CSOURCES} -o ${CLIENT}

clean:
	-rm -f *.o
	-rm -f server
	-rm -f client
