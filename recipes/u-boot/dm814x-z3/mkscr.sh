#!/bin/sh

echo "This script generates SRC u-boot environment image from the given CMD file"
echo "Usage:"
echo "      ./mksrc.sh user.cmd user.scr"

printf "%s" "Sanity check ..."

if [ -z $1 -o -z $2 ] ; then
 echo "Usage:"
 echo "      ./mksrc.sh user.cmd user.scr"
 exit -137
fi 

if [ ! -f $1 ] ; then
 echo "CMD file is not found"
 exit -137
fi
printf "%s \n" "Ok"


printf "%s" "Making environment image ..."
mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n 'Execute uImage' -d $1 $2 
printf "%s \n" "Ok"

