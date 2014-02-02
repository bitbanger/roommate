#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "roommate.h"

void bail(const char *);

int main() {
	int sock;
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		bail("socket()");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton("127.0.0.1", &addr.sin_addr);
	if(bind(sock, (struct sockaddr *)&addr, sizeof addr) < 0)
		bail("bind()");

	uint8_t buf[PCKT_LEN];
	while(true) {
		if(recv(sock, &buf, sizeof buf, 0) != PCKT_LEN) {
			fprintf(stderr, "recv(): %s\n", strerror(errno));
			continue;
		}

		if(buf[0] == MODE_LOCK) {
			if(buf[1] == LOCK_LOCKED)
				printf("Lock request received\n");
			else // buf[1] == LOCK_UNLOCKED
				printf("Unlock request received\n");
		}
	}
}

void bail(const char *problem) {
	fprintf(stderr, "%s: %s\n", problem, strerror(errno));
	exit(1);
}
