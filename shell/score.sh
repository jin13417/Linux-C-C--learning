#!/bin/bash 

if [ $1 -lt 0 ]
then
	echo "error!"
	exit
fi 
if [ $1 -gt 100 ]
	echo "error!"
	exit
fi 
if [ $1 -lt 60 ]
then
	echo "NO PASS!"
else
	if [ $1 -lt 70 ]
	then 
		echo "D"
	else
		if [ $1 -lt 80 ]
		then 
			echo "C"
		else
			if [ $1 -lt 90 ]
			then 
				echo "B"
			else
				echo "A"
			fi
		fi
	fi
fi 




