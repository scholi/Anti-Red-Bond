/*******************
 *       LIST      *
 *******************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008
*/

#ifndef H_list
#define H_list

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class list{
public:
	list();
	~list();
	void add(int x);
	int get(int id=0);
	int getlist();
	void reset();
private:
	int size;
	int *v;
	int id;
}; 
#endif
