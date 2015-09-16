/*****************************
 *          Buffer           *
 *****************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008

*/

#include "buffer.h"

buffer::buffer(int size){
	this->size=size;
	this->v=new int[size];
	#ifdef BONDARY	
	for(int i=0;i<size;i++) this->v[i]=0;
	#endif
	this->pos=0;
}

void buffer::operator<<(int x){
	this->v[this->pos++]=x;
	if(this->pos==this->size) this->pos=0;
}

int buffer::get(int i){
	return this->v[(this->pos+this->size-i-1)%this->size];
}

int buffer::get(){
	return this->get(0);
}

void buffer::set(int i, int val){
	this->v[(this->pos+this->size-i-1)%this->size]=val;
}
