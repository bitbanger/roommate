BINARIES := daemon lock unlock light lightc
CFLAGS += -std=c99 -Wall

all: ${BINARIES}
roommate.o: roommate.h

daemon: daemon.h roommate.o
daemon: CFLAGS += -lwiringPi

lock: roommate.o
unlock: lock
	cp lock unlock

light: roommate.o
lightc:	light
	cp light lightc

clean:
	- rm *.o
wipe: clean
	- rm ${BINARIES}
