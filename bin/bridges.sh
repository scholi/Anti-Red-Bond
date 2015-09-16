#!/bin/bash

size=( 4 8 16 32 64 128 256 )
pc=( 0.3609 0.34078 0.333 0.3262 0.324 0.3227 0.3225 )
num=( 1000 1000 1000 500 100 50 10 )
for (( i = 0 ; i < ${#size[@]} ; i++ ))
do
	./arb -L ${size[$i]} -d ${pc[$i]} -n ${num[$i]} -B >> data/bridges.dat 2>> data/bridges.log
done
