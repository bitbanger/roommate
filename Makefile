BINARIES := daemon lock unlock bulb light
CFLAGS += -std=c99 -Wall

all: ${BINARIES}
roommate.o: roommate.h

daemon: daemon.h roommate.o
daemon: CFLAGS += -lwiringPi

lock: roommate.o
unlock: lock
	cp lock unlock

bulb: roommate.o

light: roommate.o

clean:
	- rm *.o
wipe: clean
	- rm ${BINARIES}
