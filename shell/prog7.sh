#!/bin/bash 

for number
do
	count=`expr $number % 2`
	if [ $count -eq 1 ]
	then
		continue
	else
		output="$output $number"
	fi
done
echo "even numbers: $output"
