#!/bin/sh

userbin() {
	[ -e /usr/local/bin/$1 ] && rm -f /usr/local/bin/$1
	cp $1 /usr/local/bin/
	chgrp staff /usr/local/bin/$1
	chmod g+x,o= /usr/local/bin/$1
}

if ! ( groups | grep -q staff )
	then
		echo Please add yourself to the staff group, log out, and log back in.
		exit 1
	fi

if ! make
	then
		exit 1
	fi

[ -e /usr/local/sbin/daemon ] && rm -f /usr/local/sbin/daemon
cp daemon /usr/local/sbin/

if [ ! -e /etc/init.d/roommate ]
	then
		sudo cp roommate.init.d /etc/init.d/roommate
		sudo ln -s /etc/init.d/roommate /etc/rc2.d/S05roommate
	fi

userbin lock
userbin unlock
userbin doorlog
userbin bulb
userbin light

if [ ! -e /var/log/roommate ]
	then
		sudo touch /var/log/roommate
		sudo chgrp staff /var/log/roommate
		sudo chmod g+w,o= /var/log/roommate
	fi
