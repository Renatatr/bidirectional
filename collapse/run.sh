#!/bin/bash
rm sur.txt
for I in $(seq 10 1 30)
do
	cd r$I
		./run.sh
	cd ../
done

for I in $(seq 10 1 30)
do
	cd r$I/died
	cat d.dat | awk '{print $1}' |head -n1 |tail -1 >> ../../A.dat
cd ../../
done

for I in $(seq 10 1 30)
do
	echo $I >> seq.dat
done

paste seq.dat A.dat >> sur.txt

rm *.dat
