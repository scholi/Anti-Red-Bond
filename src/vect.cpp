/***************
 *    Vector   *
 ***************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008

*/

#include "vect.h"

vect::vect(){
	this->size=0;
	this->v=(int*)calloc(1000,sizeof(int));
	this->msize=1000;
}

vect::~vect(){
	free(this->v);
}

int vect::get(int i){
	if(i>=this->size) return 0;
	return this->v[i];
}

void vect::set(int i, int val){
	if(i>=this->msize){
		this->msize+=1000;
		this->v=(int*)realloc(this->v,sizeof(int)*this->msize);
	}
	for(int j=this->size;j<i;j++){
		this->v[j]=0;
	}
	if(i>1) this->v[i]=val;
	if(i>=this->size) this->size=i+1;
}

int vect::follow(int x){
	int r=this->get(x);
	if(r==1) return 1;
	else if(r>1){
		return this->follow(r);
	}
	return x;
}

void vect::shortening(){
	for(int i=0;i<this->size;i++){
		this->set(i,this->follow(this->get(i)));
	}
}

void vect::update(int j, vect* b){
	for(int i=0;i<this->size;i++){
		if(this->get(i)==j) this->set(i,1);
	}
}

void vect::write(const char* filename){
	std::ofstream fn(filename);
	for(int i=0;i<this->size;i++){
		fn << this->follow(this->get(i)) << "\n";
	}
	fn.close();
}
