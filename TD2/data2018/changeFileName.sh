#!/bin/bash

#find *.txt -exec head -n 101 > {} \;

#n = $#
#echo $n
# let "cond = TRUE" 
let "i = 1"
fileName="coucou"
while [ $i -le $# ]
do
	#TD7-File01-N100-C10e3.txt
	fileName="$1"
	part1=${fileName:0:2}
	part2='2'
	part3=${fileName:3}
	fileName="$part1$part2$part3"
	mv $1 $fileName
	shift
done
