BINARIES := daemon lock unlock light
CFLAGS += -std=c99

all: ${BINARIES}
roommate.o: roommate.h

daemon: daemon.h roommate.o
daemon: CFLAGS += -lwiringPi

lock: roommate.o
unlock: lock
	cp lock unlock

light: roommate.o

clean:
	- rm *.o
wipe: clean
	- rm ${BINARIES}
