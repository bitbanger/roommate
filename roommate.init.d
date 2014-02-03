#!/bin/sh

case $1 in
        start)
		/usr/local/sbin/daemon &
                ;;
        stop)
		killall daemon
                ;;
        restart)
		killall daemon
		/usr/local/sbin/daemon &
                ;;
esac
