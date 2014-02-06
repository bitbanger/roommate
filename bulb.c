#include <stdio.h>
#include <string.h>
#include "roommate.h"

int main(int argc, char **argv) {
	uint8_t msg[PCKT_LEN];
	memset(msg, 0, sizeof msg);

	msg[0] = MODE_LIGHTSWITCH; // cock-a-doodle-doo

	if(argc == 2 && strcmp(argv[1], "off") == 0)
		msg[1] = LIGHTSWITCH_OFF;
	else if(argc == 2 && strcmp(argv[1], "on") == 0)
		msg[1] = LIGHTSWITCH_ON;
	else {
		printf("USAGE: %s <off|on>\n", argv[0]);
		return 1;
	}	
	
	sendpkt(msg);
	return 0;
}
