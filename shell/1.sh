#!/bin/bash 
if [ $# -ne 1 ]
then 
	echo "erro!"
	exit
fi 
if [ -f $1 ]
then 

	echo "`tput smul` $1 `tput rmul` is a `tput bold` link file `tput sgr0`"
else
	if [ -f $1 ]
	then
		echo $?
		echo "$1 is a regular file."
	else
		if [ -d $1 ]
		then
			echo "$1 is a directory"
		else
			echo ":$1 is unknown format~"
		fi
	fi
fi
