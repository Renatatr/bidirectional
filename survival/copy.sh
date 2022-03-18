#!/bin/bash
 
# created     : 2018/12/28
# last update : 2021/02/10
# author      : breno <breno@dfi.uem.br>
# notes       : 
LANG=en_us 
I=0
for J in $(seq 0.0 0.01 1.0)
do
	echo $I - $J
	cp -r base $I
	sed -i "16 s/1.00/$J/" $I/rps.h
	I=$(($I+1))
done 

I=0
for J in $(seq 0.0 0.01 1.0)
do
	echo $I - $J
	cd $I
	make clean
	make
	cd ..
	I=$(($I+1))
done 

