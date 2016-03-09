#!/bin/sh
#
# hostname.sh   Set hostname.

ethaddr=`cat /sys/class/net/eth0/address`

if test -f /etc/hostname; then
   hostname=`cat /etc/hostname`
   hostname="${hostname}-${ethaddr}"
else
   hostname="${ethaddr}"
fi

   hostname ${hostname}

