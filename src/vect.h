/*************************
 *      Vector class     *
 *************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008

*/

#ifndef H_vect
#define H_vect

#include <iostream>
#include <fstream>
#include <cstdlib>

class vect{
public:
	vect();
	~vect();
	void set(int i, int val);
	int get(int i);
	int follow(int x);
	void shortening();
	void update(int j, vect* b);
	void write(const char* filename);
private:
	int *v;	
	int size;
	int msize;
};

#endif
