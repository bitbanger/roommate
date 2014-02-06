#ifndef ROOMMATE_H
#define ROOMMATE_H

#include <stdint.h>

extern const int PORT;
extern const int PCKT_LEN;

extern const char MODE_LOCK;
extern const uint8_t LOCK_LOCKED;
extern const uint8_t LOCK_UNLOCKED;

extern const char MODE_LIGHT;

extern const char *LOGFILE_PATH;

void sendpkt(const uint8_t *);
void logline(const char *, ...);
void bail(const char *);

#endif
