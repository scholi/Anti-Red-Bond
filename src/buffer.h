/*****************************
 *          Buffer           *
 *****************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008
*/
#ifndef H_buffer
#define H_buffer

#include <stdio.h>
#include <stdlib.h>

class buffer{
public:
	buffer(int size);
	void operator<<(int x);
	int get(int i);
	int get();
	void set(int i, int v);
private:
	unsigned int pos;
	int size;
	int *v;
};

#endif 
