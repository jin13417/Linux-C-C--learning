#!/bin/bash 

i=1
while [ $i -lt 21 ]
do
touch file_$i.sh
echo a b c d e f g >> file_$i.sh
rm file_$i.sh 
	i=`expr $i + 1`
done
 

