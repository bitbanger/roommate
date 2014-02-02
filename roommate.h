#include <stdint.h>

#ifndef ROOMMATE_H
#define ROOMMATE_H

extern const int PORT;
extern const int PCKT_LEN;

extern const char MODE_LOCK;
extern const char LOCK_LOCKED;
extern const char LOCK_UNLOCKED;

extern const char *LOGFILE_PATH;

void sendpkt(const uint8_t *);
void logline(const char *, ...);
void bail(const char *);

#endif
