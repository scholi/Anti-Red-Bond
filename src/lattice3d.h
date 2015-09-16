/*****************************
 *   Lattice - 3D Lattice    *
 *****************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008
*/

#ifndef H_lattice3D_arb
#define H_lattice3D_arb

#include "CONFIG.h"
#include "buffer.h"
#include "list.h"
#include "blist.h"
#include "vect.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

extern bool CALCULATE_ONLY_PERCOL;
extern bool BRIDGESINFO;
extern bool CALCULATE_ONLY_BRIDGES;
extern bool EXPORT;

class lattice{
public:
	lattice(int sx, int sy, int sz, double p); // size: sx*sy; density: p
	~lattice();
	int hkarbc(); //Hoshen-Kopelman Anti-Red Bound Calculation
	
	void copydown();
	void copyleft();
	void lookbridge(int x, int y, int z);
private:
	vect *pointer;
	blist *bridges;
	int sx;	// X-Size
	int sy;	// Y-Size
	int sz; // Z-Size
	int top_max;
	double p;	// Density
	buffer *r; // Store 2 (rows) plans
	#ifdef BENCHMARK
	time_t startt, endt;
	double time_scan, time_update;
	#endif
};

#endif
