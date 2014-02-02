#include <stdint.h>

#ifndef ROOMMATE_H
#define ROOMMATE_H

const int PORT;
const int PCKT_LEN;

const char MODE_LOCK;
const char LOCK_LOCKED;
const char LOCK_UNLOCKED;

const char *LOGFILE_PATH;

void sendpkt(const uint8_t *);
void logline(const char *, ...);
void bail(const char *);

#endif
