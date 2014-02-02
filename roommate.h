#ifndef ROOMMATE_H
#define ROOMMATE_H

const int PORT;
const int PCKT_LEN;

const char MODE_LOCK;
const char LOCK_LOCKED;
const char LOCK_UNLOCKED;

void sendpkt(const char *);

void bail(const char *);

#endif
