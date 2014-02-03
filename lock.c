// TODO: get rid of this when we axe cuserid()
#define _XOPEN_SOURCE

#include <sys/socket.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
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

	time_t rightnow = time(NULL);
	struct tm *stamp = localtime(&rightnow);

	char timestamp[100]; // probably big enough...
	strftime(timestamp, sizeof timestamp, "%a %F %T", stamp);
	logline("%s := Door %s by %s\n", timestamp, msg[1] == LOCK_LOCKED ? "locked" : "unlocked", cuserid(NULL)); // TODO: fix this shit because cuserid() sucks
	
	return 0;
}
