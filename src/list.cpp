/*******************
 *       LIST      *
 *******************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008
*/
#include "list.h"

list::list(){
	this->size=0;
	this->v=(int*)malloc(sizeof(int)*1000);
	this->id=0;
}

list::~list(){
	free(this->v);
}

void list::add(int x){
	this->v[this->size++]=x;
	if(this->size%1000==0){ // reallocate memory space if needed
		this->v=(int*)realloc(this->v,sizeof(int)*(this->size+1000));
	}
}

int list::get(int id){
	if(id>0 && id<this->size)
		return this->v[id];
	return 0; // Error
}

int list::getlist(){
	if(this->id<this->size)
		return this->v[this->id++];
	return 0;
}

void list::reset(){
	this->id=0;
}
