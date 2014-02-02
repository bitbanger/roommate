BINARIES := daemon lock unlock

all: ${BINARIES}
roommate.o: roommate.h

daemon: daemon.h roommate.o
daemon: CFLAGS += -lwiringPi

lock: roommate.o
unlock: lock
	cp lock unlock

clean:
	- rm *.o
wipe: clean
	- rm ${BINARIES}
