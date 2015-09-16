/*****************************
 *   BLIST - List Bridges    *
 *****************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html9
 File Version: 1.0
 Date: 05 june 2008
 Description:	blist class manage the list of bridges.
		Each bridge is managed by the class element

*/

#include "blist.h"

element::element(int px, int py, int pz, int n, int v[]){
	this->v=new int[n+3];
	this->v[n]=px;
	this->v[n+1]=py;
	this->v[n+2]=pz;
	this->s=n;
	for(int i=0;i<n;i++) this->v[i]=v[i];
}
element::element(int n, int v[]){
	this->v=new int[n];
	this->s=n;
	for(int i=0;i<n;i++) this->v[i]=v[i];
} 

int element::getx(){
	if(EXPORT){
		return this->v[this->s];
	}else return 0;
}
int element::gety(){
	if(EXPORT){
		return this->v[this->s+1];
	}else return 0;
}
int element::getz(){
	if(EXPORT){
		return this->v[this->s+2];
	}else return 0;
}

element::~element(){
	delete this->v;
}

void element::write(std::ofstream &o){
	if(EXPORT){
		o << "(" << this->getx() << "," << this->gety() << "," << this->getz() <<") ";
	}
	for(int i=0;i<this->s;i++) o << this->v[i] << " ";
	o << "\n";
}

void element::update(int b, int a){
	for(int i=0;i<this->s;i++){
		if(this->v[i]==b) this->v[i]=a;
	}
}

bool element::has_id(int id, vect *pointer){
	for(int i=0;i<this->s;i++)
		if(pointer->follow(this->v[i])==pointer->follow(id))
			return true;
	return false;
}

bool element::has_id_top(int top_max, vect *pointer){
	for(int i=0;i<this->s;i++) if(pointer->follow(this->v[i])<=top_max && this->v[i]>1) return true;
	return false;
}

int element::num_id(){
	int n=0;
	for(int i=0;i<this->s;i++){
		n++;
		for(int j=0;j<i;j++){
			if(this->v[i]==this->v[j]) n--;
		}
	}
	return n;
}

int element::get(int id){
	return this->v[id];
}

int element::num(){
	return this->s;
}
// ====================================================================

blist::blist(){
	this->size=0;
	this->elts=(element**) malloc(sizeof(element*)*1000);
}

blist::~blist(){
	for(int i=0;i<this->size;i++) delete this->elts[i];
	free(this->elts);
}

void blist::add(int x, int y, int z, int n, int v[]){
	this->elts[this->size++]=new element(x,y,z,n,v);
	if(this->size%1000==0){
		this->elts=(element**) realloc(this->elts,sizeof(element*)*(this->size+1000));
	}
}
void blist::add(int n, int v[]){
	this->elts[this->size++]=new element(n,v);
	if(this->size%1000==0){
		this->elts=(element**) realloc(this->elts,sizeof(element*)*(this->size+1000));
	}
}

void blist::write(std::ofstream &o){
	for(int i=0;i<this->size;i++) this->elts[i]->write(o);
}

void blist::update(int b, int a){
	for(int i=0;i<this->size;i++){
		this->elts[i]->update(b,a);
	}
}

int blist::scan(int top_max, vect *pointer){
	std::ofstream *f;
	if(EXPORT) f=new std::ofstream("arb.dat");
	int n=0;
	for(int i=0;i<this->size;i++){ // scan over all bridges
		bool ltb=false;
		bool ltt=false;
		for(int id=0;id<this->elts[i]->num() and !(ltb and ltt);id++){
			int cid=pointer->follow(this->elts[i]->get(id));
			if(cid>1 && cid<=top_max) ltt=true;
			else if(cid==1) ltb=true;
		}
		//std::clog << "@ " << i << "/" << this->size << "\t" << (ltt?"TOP\t":"") << (ltb?"BOTTOM\t":"") << "\n";
		if(ltt and ltb){
				if(EXPORT){
					*f << this->elts[i]->getx() << "\t" << this->elts[i]->gety() << "\t" << this->elts[i]->getz() << "\n";
				}
				n++;
		}
	}
	if(EXPORT){ f->close(); delete f; }
	return n;
}

int blist::num(){
	return this->size;
}
