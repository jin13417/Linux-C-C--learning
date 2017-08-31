#!/bin/bash 

cat $1 |
while read line
do
  
a=`echo $line | cut -d '.' -f1`
b=`echo $line | cut -d '.' -f2`
c=`echo $line | cut -d '.' -f3`
d=`echo $line | cut -d '.' -f4`
num=`expr $a \* 256 \* 256 \* 256 + $b \* 256 \* 256 + $c \* 256 + $d`
echo $num >> ip2.c

done

