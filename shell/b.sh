#!/bin/bash 


if [ $1 -lt 0 ] || [ $1 -gt 100 ]
then
	echo "error!"
	exit
fi 
	i=`expr $1 / 10`
	case $i in
		1)
			echo "NO PASS"
			;;
		2)
			echo "NO PASS"
			;;
		3)
			echo "NO PASS"
			;;
		4)
			echo "NO PASS"
			;;
		5)
			echo "NO PASS"
			;;
		6)
			echo "D"
			;;
		7)
			echo "C"
			;;
		8)
			echo "B"
			;;
		*)
			echo "A"
			;;
	esac
