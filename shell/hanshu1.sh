#!/bin/bash 

check_user()
{
	user=`who | grep $1 | wc -l`
	if [ $user -eq 0 ]
	then
		return 0
	else
		return 1
	fi

	}
	while true
	do
		echo "input username:\c"
		read uname
		check_user $uname
		if [ $? -eq 1 ]
		then
			echo "user $uname online"
		else
			echo "user $uname offline"
		fi
	done


