#!/bin/bash
 
# created     : 2018/12/28
# last update : 2021/02/10
# author      : breno <breno@dfi.uem.br>
# notes       : 
LANG=en_us 
I=5
for J in $(seq 5 1 30)
do
	echo $I - $J
	cp -r base r$I
	sed -i "8 s/10/$J/" r$I/src/ic.c
	I=$(($I+1))
done 

I=5
for J in $(seq 5 1 30)
do
	echo $I - $J
	cd r$I
	make clean
	make
	cd ..
	I=$(($I+1))
done 

