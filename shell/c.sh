#!/bin/bash 

MY_PATH="/etc/passwd"
DIR="mywork"
INFO="/var/info"

usr=`whoami`
uid=`cat $MY_PATH | grep $usr | cut -d ':' -f3`
gid=`cat $MY_PATH | grep $usr | cut -d ':' -f4`

if [ $usr = "root" ]
then
	MY_HOME="/root"
else
	MY_HOME="/home/$usr"
fi
cd $MY_HOME
if [ -e $DIR ]
then
	if ! [ -d $DIR ]
	then
		echo "file exit !"
		exit
	fi
else
	mkdir $DIR
fi
tail -500 $MY_HOME/.bash_history > "$MY_HOME/$DIR/cmd_$uid"
for tmp_file in `ls -a $MY_HOME`
do
	if [ -f $tmp_file ]
	then
		if [ -r $tmp_file ]
		then
			echo $tmp_file >> $MY_HOME/$DIR/file_$gid
		fi
	fi
done
echo ----------------->> $INFO
echo $usr >> $INFO
echo -n "cmd_$uid  ">>$INFO
cat $MY_HOME/$DIR/cmd_$uid | wc -l >> $INFO
echo -n "cmd_$gid  ">>$INFO
cat $MY_HOME/$DIR/cmd_$gid | wc -l >> $INFO
