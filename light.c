#include <sys/stat.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "roommate.h"

int main(int argc, char **argv) {
	uint8_t msg[PCKT_LEN];
	msg[0] = MODE_LIGHT;

	char *ename = basename(argv[0]);

	int col[3] = {0, 0, 0}; // RGB
	
	if(strcmp(ename, "lightc") == 0) {
		if(argc != 2) {
			printf("USAGE: %s <colorname\n", argv[0]);
			exit(1);
		}
		
		// Load up the RGB text file and search for the color
		FILE *fd = fopen("/etc/X11/rgb.txt", "r");
		
		char linebuf[256];
		
		while(fgets(linebuf, 256, fd)) {
			linebuf[3] = '\0';
			col[0] = atoi(linebuf);
			linebuf[7] = '\0';
			col[1] = atoi(linebuf + 4);
			linebuf[11] = '\0';
			col[2] = atoi(linebuf + 8);
			
			// fuck the X11 people
			char *colname = (linebuf + 12);
			while(*colname == '\t' || *colname == ' ') ++colname;
			
			int nlpos = strlen(colname) - 1;
			if(colname[nlpos] == '\n') {
				colname[nlpos] = '\0';
			}
			
			if(strcasecmp(argv[1], colname) == 0) {
				if(strcasecmp(argv[1], "PeachPuff") == 0) {
					fprintf(stderr, "Are you fucking serious?\n");
				}
				break;
			}
		}
		
		if(feof(fd)) {
			fclose(fd);
			exit(1);
		}
		
		fclose(fd);
	} else if(argc == 4) {
		int ch;
		for(ch = 0; ch < 3; ++ch) {
			col[ch] = atoi(argv[ch + 1]); // TODO: validate
		}
	} else if(argc == 2) {
		// parse the hex string in groups of two bytes into values
		char clr[3];
		memset(clr, 0, 3);
		for(int i = 0; i < 3; ++i) {
			clr[0] = argv[1][i * 2];
			clr[1] = argv[1][i * 2 + 1];
			col[i] = (uint8_t)strtol(clr, NULL, 16);
		}
	} else {
		printf("USAGE: %s <red> <green> <blue> OR %s <hexrgb>\n", argv[0], argv[0]);
		printf("\tEach color is a decimal integer between 0 and 256, or pass one six-digit hex string.\n");
		exit(1);
	}
	
	int i;
	for(i = 0; i < 3; ++i) msg[i + 1] = col[i];

	sendpkt(msg);

	return 0;
}
