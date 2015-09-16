/*******************
 *    Statistics   *
 *******************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.0
 Date: 05 june 2008

*/ 
#include "stat.h"

stat::stat(){
	this->n=0;
	this->s=this->s2=0;
} 

stat::~stat(){

}

double stat::err(){
	if(this->n==0) return 0;
	return this->stddev()/sqrt(this->n);
}

stat& stat::operator<<(double x){
	this->s+=x;
	this->s2+=(x*x);
	this->n++;
	return (*this);
}

double stat::mean(){
	if(this->n==0) return 0;
	return this->s/this->n;
}

double stat::var(){
	if(this->n==0) return 0;
	return (this->s2/this->n)-(this->mean()*this->mean());
}

double stat::stddev(){
	return sqrt(this->var());
}

int stat::num(){
	return this->n;
}

void stat::reset(){
	this->s=this->s2=this->n=0;
}
