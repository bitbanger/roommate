#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "roommate.h"

int main(int argc, char **argv) {
	uint8_t msg[PCKT_LEN];
	msg[0] = MODE_LIGHT;

	if(argc == 4) {
		for(int ch = 1; ch < 4; ++ch) {
			msg[ch] = atoi(argv[ch]); // TODO: validate
		}
	} else if(argc == 2) {
		// parse the hex string in groups of two bytes into values
		char clr[3];
		memset(clr, 0, 3);
		for(int i = 0; i < 3; ++i) {
			clr[0] = argv[1][i * 2];
			clr[1] = argv[1][i * 2 + 1];
			msg[i + 1] = (uint8_t)strtol(clr, NULL, 16);
		}
	} else {
		printf("USAGE: %s <red> <green> <blue> OR %s <hexrgb>\n", argv[0]);
		printf("\tEach color is a decimal integer between 0 and 256, or pass one six-digit hex string.\n");
		exit(1);
	}

	sendpkt(msg);

	return 0;
}
