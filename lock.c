#include <sys/socket.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roommate.h"

int main(int argc, char **argv) {
	char *ename = basename(argv[0]);

	uint8_t msg[PCKT_LEN];
	int i;
	memset(msg, 0, sizeof msg);

	msg[0] = MODE_LOCK; // cock blocked

	if(strcmp(ename, "lock") == 0) {
		msg[1] = LOCK_LOCKED;
	} else if(strcmp(ename, "unlock") == 0) {
		msg[1] = LOCK_UNLOCKED;
	} else {
		printf("have a nice day ;)\n");
		return 0;
	}	
	
	sendpkt(msg);
	
	return 0;
}

