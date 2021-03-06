#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "roommate.h"

int main(int argc, char **argv) {
	uint8_t msg[PCKT_LEN];
	msg[0] = MODE_LIGHT;

	int col[3] = {0, 0, 0}; // RGB
	
	if(argc == 4) {
		for(int ch = 0; ch < 3; ++ch) {
			col[ch] = atoi(argv[ch + 1]); // TODO: validate
		}
	} else if(argc == 2) {
		if(argv[1][0] == '0' && argv[1][1] == 'x') {
			// parse the hex string in groups of two bytes into values
			char clr[3];
			memset(clr, 0, 3);
			for(int i = 0; i < 3; ++i) {
				clr[0] = argv[1][i * 2 + 2];
				clr[1] = argv[1][i * 2 + 3];
				col[i] = (uint8_t)strtol(clr, NULL, 16);
			}
		} else {
			// First, check our defined aliases
			if(strcasecmp(argv[1], "on") == 0) {
				col[0] = 255;
				col[1] = 255;
				col[2] = 255;
			} else if(strcasecmp(argv[1], "off") == 0) {
				col[0] = 0;
				col[1] = 0;
				col[2] = 0;
			} else {
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
					fprintf(stderr, "Color '%s' not found. Please consult /etc/X11/rgb.txt for a list of color names.\n", argv[1]);
					fclose(fd);
					return 1;
				}
				
				fclose(fd);
			}
		}
	} else {
		printf("USAGE: %s <red> <green> <blue> OR %s 0x<hexrgb> OR %s <colorname>\n", argv[0], argv[0], argv[0]);
		printf("\tEach color is a decimal integer between 0 and 256, or pass one six-digit hex string, or give a color name from the X11 color list found at /etc/X11/rgb.txt .\n");
		return 1;
	}
	
	for(int i = 0; i < 3; ++i) msg[i + 1] = col[i];

	sendpkt(msg);
	return 0;
}
