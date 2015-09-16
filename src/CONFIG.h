//#define BENCHMARK
//#define VERBOSE
//#define DEBUG
//#define KEEP_ALL_LATTICE_IN_RAM

#ifndef RND_H
#define RND_H
#include <stdlib.h>
#include <fstream>
#include <iostream>

inline double xrnd(){
/*	std::ifstream rgn("/dev/urandom");
	unsigned int i;
	char *d;	
	d=(char*)(&i);
	for(int j=0;j<4;j++) rgn >> d[j];
//	std::cout << i << "\t" << (double)(i)/0xffffffff << "\n";
	return (double)(i)/0xffffffff;*/
	return (double)(rand())/RAND_MAX;
}
#endif
