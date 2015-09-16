/*****************************
 *   BLIST - List Bridges    *
 *****************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008
 Description:	blist class manage the list of bridges.
		Each bridge is managed by the class element
*/

#ifndef H_blist
#define H_blist

#include "CONFIG.h"
#include "list.h"
#include "vect.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

extern bool EXPORT;

class element{
public:
	element(int px, int py, int pz, int n, int v[]);
	element(int n, int v[]);
	~element();
	int getx();
	int gety();
	int getz();
	void write(std::ofstream &o);
	void update(int b, int a);
	bool has_id(int id, vect *pointer);
	bool has_id_top(int top_max, vect *pointer);
	int num_id();
	int get(int id);
	int num();
private:
	int *v;
	char s;
};

class blist{
public:
	blist();
	~blist();
	void add(int x, int y, int z, int n, int v[]);
	void add(int n, int v[]);
	void update(int b, int a);
	void write(std::ofstream &o);
//	int has_id(int a, int top_max);
	int scan(int top_max, vect *pointer);
	int num();
private:
	int size;
	element **elts;
};

#endif 
