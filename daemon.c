#define _BSD_SOURCE

#include <arpa/inet.h>
#include <errno.h>
#include <softPwm.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include "daemon.h"
#include "roommate.h"

int main() {
	int sock;
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		bail("socket()");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	if(bind(sock, (struct sockaddr *)&addr, sizeof addr) < 0)
		bail("bind()");

	const int LED_RANGE = 256 >> LED_DOWNSHIFT;
	wiringPiSetup();
	softPwmCreate(GPIO_DOOR_SERVO, DOOR_SERVO_LOCKED, DOOR_SERVO_RANGE);
	pinMode(GPIO_DOOR_SERVO, INPUT);
	softPwmCreate(GPIO_LIGHT_SERVO, LIGHT_SERVO_OFF, LIGHT_SERVO_RANGE);
	pinMode(GPIO_LIGHT_SERVO, INPUT);
	softPwmCreate(GPIO_RED, LED_RANGE, LED_RANGE);
	softPwmCreate(GPIO_GREEN, LED_RANGE, LED_RANGE);
	softPwmCreate(GPIO_BLUE, LED_RANGE, LED_RANGE);

	uint8_t buf[PCKT_LEN];
	while(true) {
		pinMode(GPIO_DOOR_SERVO, INPUT);
		pinMode(GPIO_LIGHT_SERVO, INPUT);

		if(recv(sock, &buf, sizeof buf, 0) != PCKT_LEN) {
			fprintf(stderr, "recv(): %s\n", strerror(errno));
			continue;
		}

		if(buf[0] == MODE_LOCK) {
			if(buf[1] == LOCK_LOCKED) {
				softPwmWrite(GPIO_DOOR_SERVO, DOOR_SERVO_LOCKED);
			}
			else { // buf[1] == LOCK_UNLOCKED
				softPwmWrite(GPIO_DOOR_SERVO, DOOR_SERVO_UNLOCKED);
			}
			pinMode(GPIO_DOOR_SERVO, OUTPUT);
			usleep(DOOR_SERVO_DURATION); // TODO: don't block here
		}
		else if(buf[0] == MODE_LIGHTSWITCH) {
			if(buf[1] == LIGHTSWITCH_OFF) {
				softPwmWrite(GPIO_LIGHT_SERVO, LIGHT_SERVO_OFF);
			}
			else { // buf[1] == LIGHTSWITCH_ON
				softPwmWrite(GPIO_LIGHT_SERVO, LIGHT_SERVO_ON);
			}
			pinMode(GPIO_LIGHT_SERVO, OUTPUT);
			usleep(LIGHT_SERVO_DURATION); // TODO: don't block here
		}
		else if(buf[0] == MODE_LIGHT) {
			// We invert the number and add a number so we can safely chop off the downshift blocks or some shit
			int inv = 255 + (1 << LED_DOWNSHIFT);

			int red = (inv - buf[1]) >> LED_DOWNSHIFT;
			int green = (inv - buf[2]) >> LED_DOWNSHIFT;
			int blue = (inv - buf[3]) >> LED_DOWNSHIFT;

			softPwmWrite(GPIO_RED, red);
			softPwmWrite(GPIO_GREEN, green);
			softPwmWrite(GPIO_BLUE, blue);
		}
	}
}
