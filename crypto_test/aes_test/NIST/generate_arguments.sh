#!/bin/bash
pos1=1
pos2=4
controle=0
aantal=0
for file in $(ls |grep CBC); do
    aantal=$(cat $file |wc -l)
    aantal=$(($aantal/4))
    controle=0
    pos1=1
    pos2=4
    while [ $controle -lt $aantal ]; do
	controle=$(($controle+1))
	sed -n "$pos1,$pos2 p" $file |tr '\n' ' '
	echo ""
	pos1=$(($pos2+1))
	pos2=$(($pos2+4))

	
    done
done
