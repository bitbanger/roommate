#!/bin/sh

if ! ( groups | grep -q staff )
	then
		echo Please add yourself to the staff group, log out, and log back in.
		exit 1
	fi

if ! make
	then
		exit 1
	fi

[ -e /usr/local/bin/lock -o -e /usr/local/bin/unlock ] && rm /usr/local/bin/lock /usr/local/bin/unlock

cp lock unlock doorlog /usr/local/bin/
chgrp staff /usr/local/bin/lock /usr/local/bin/unlock /usr/local/bin/doorlog
chmod g+x,o= /usr/local/bin/lock /usr/local/bin/unlock /usr/local/bin/doorlog

if [ ! -e /var/log/roommate ]
	then
		sudo touch /var/log/roommate
		sudo chgrp staff /var/log/roommate
		sudo chmod g+w,o= /var/log/roommate
	fi
