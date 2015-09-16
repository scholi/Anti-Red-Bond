#!/bin/bash

size=8

for p in `seq 0 0.0001 0.4`
do
	./arb -L $size -d $p -n 1000 >> arb8.dat 2>> arb8.log
done
