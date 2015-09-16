/*******************
 *    Statistics   *
 *******************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008

*/ 

#ifndef H_stat
#define H_stat

#include <iostream>
#include <math.h>

class stat{
public:
	stat();
	~stat();
	stat& operator<<(double x);
	double mean();
	double var();
	int num();
	double stddev();
	void reset();
	double err();
private:
	double s;
	double s2;
	int n;
};

#endif 
