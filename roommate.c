#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roommate.h"

const int PORT = 1030;
const int PCKT_LEN = 4; // B

const char MODE_LOCK = 'l';
const char LOCK_LOCKED = 0;
const char LOCK_UNLOCKED = 1;

const char *LOGFILE_PATH = "/var/log/roommate";

void sendpkt(const uint8_t *pkt) {
	int sfd = -1;
	if((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		bail("socket()");
	
	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton("127.0.0.1", &addr.sin_addr);

	if(sendto(sfd, pkt, PCKT_LEN, 0, (struct sockaddr *)&addr, sizeof addr) < 0)
		bail("sendto()");

	close(sfd);
}

void logline(const char *msg, ...) {
	va_list args;
	FILE *file = fopen(LOGFILE_PATH, "a");

	va_start(args, msg);
	vfprintf(file, msg, args);
	va_end(args);
	close(file);
}

void bail(const char *problem) {
        fprintf(stderr, "%s: %s\n", problem, strerror(errno));
        exit(1);
}

