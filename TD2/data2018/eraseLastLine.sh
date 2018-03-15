#!/bin/bash

#find *.txt -exec head -n 101 > {} \;

#n = $#
#echo $n
# let "cond = TRUE" 
let "i = 1"
while [ $i -le $# ]
do
	#wc -l $1
	#tail -n 101 $1 > $1
	nombredelignes=$(wc -l $1 | cut -d" " -f1)
	head -$(expr $nombredelignes - 1) $1 >> tmp.txt
	cat tmp.txt > $1
	rm tmp.txt
	shift
done
