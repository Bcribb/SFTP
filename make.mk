CC = gcc
CFLAGS = -g -Wall -Wfatal-errors std=g++11

output: server.o client.o
    $(CC) $(CFLAGS) -o 
