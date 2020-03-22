CC=g++
CCFLAGS=-g -std=c++11 -pedantic -Wall
INC=
LK=g++
LIBS=-lpthread

PROG=clserver
OBJS=server.o manager.o

$(PROG) : $(OBJS)
	$(LK) $(LKFLAGS) $(OBJS) $(LIBS) -o $(PROG)

all : clean $(PROG)

server.o : server.cpp
	$(CC) -c $(CCFLAGS) server.cpp -o server.o
	
manager.o : manager.h manager.cpp
	$(CC) -c $(CCFLAGS) manager.cpp -o manager.o

clean :
	rm -rf *.o *.*~
	rm -rf $(PROG)
