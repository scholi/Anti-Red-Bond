/*****************************
 *   Lattice - 3D Lattice    *
 *****************************

 Author: Olivier Scholder
 Licence: GPL (http://gnu.org/licenses/gpl.html)
 File Version: 1.1
 Date: 05 june 2008
*/

#include "lattice3d.h"

void lattice::copydown(){
	if(this->r->get(this->sx*this->sy)>0){
		int ace=this->r->get();
		int aup=this->r->get(this->sx*this->sy);
		bool ch=true;
		if(ace<aup){
			int t=ace; ace=aup; aup=t; ch=false;
		}
		int anew=this->pointer->follow(aup);
		if(ace!=anew){
			this->pointer->set(ace,anew);
			this->r->set(0,anew);
		}
	}
}

void lattice::copyleft(){
	if(this->r->get(this->sx)>0){
		int ace=this->r->get();
		int aup=this->r->get(this->sx);
		bool ch=true;
		if(ace<aup){
			//ace^=aup^=ace^=aup; ch=false; (not efficient?)
			int t=ace; ace=aup; aup=t; ch=false;
		}
		//this->bridges->update(ace,aup); // Take the smallest ID
		int anew=this->pointer->follow(aup);
		if(ace!=anew) this->pointer->set(ace,anew);
		for(int i=0;this->r->get(i)==ace;i++) this->r->set(i,anew);
		//for(int i=0;i<this->sx;i++) this->r->set(i,anew);
	}
}

void lattice::lookbridge(int x, int y, int z){
	if(this->r->get(this->sx*this->sy)==0){ // up cell empty?
		int n=0;
		int v[6]={0,0,0,0,0,0};
		bool found=false;
		if(this->r->get(2*(this->sx*this->sy))>0 && z>1){ // two cell up not empty?
			v[n++]=this->r->get(2*(this->sy*this->sx));
		}
		if(this->r->get((this->sy*this->sx)-1)>0 && x<(this->sx-1)){
			for(int j=0;j<n;j++) if(this->r->get((this->sy*this->sx)-1)==v[j]){ found=true; break; }
			if(!found) v[n++]=this->r->get((this->sy*this->sx)-1);
		}
		found=false;
		if(this->r->get((this->sx*this->sy)+1)>0 && x>0){
			for(int j=0;j<n;j++) if(this->r->get((this->sy*this->sx)+1)==v[j]){ found=true; break; }
			if(!found) v[n++]=this->r->get((this->sx*this->sy)+1);
		}
		found=false;
		if(this->r->get((this->sx*this->sy)+this->sx)>0 && y>0){
			for(int j=0;j<n;j++) if(this->r->get((this->sy*this->sx)+this->sx)==v[j]){ found=true; break; }
			if(!found) v[n++]=this->r->get((this->sx*this->sy)+this->sx);
		}
		found=false;
		if(this->r->get((this->sx*this->sy)-this->sx)>0 && y<(this->sy-1)){
			for(int j=0;j<n;j++) if(this->r->get((this->sy*this->sx)-this->sx)==v[j]){ found=true; break; }
			if(!found) v[n++]=this->r->get((this->sx*this->sy)-this->sx);
		}
		found=false;
		if(this->r->get()>0){
			for(int j=0;j<n;j++) if(this->r->get()==v[j]){ found=true; break; }
			if(!found) v[n++]=this->r->get();
		}
		if(z==1) v[n++]=2;
		if(EXPORT){
			if(n>1) this->bridges->add(x,y,z-1,n,v);
		}else{
			if(n>1) this->bridges->add(n,v);
		}
	}
}


lattice::lattice(int sx, int sy, int sz, double p){
	#ifdef DEBUG
	std::clog << "@1\n";
	#endif
	this->pointer=new vect();
	this->sx=sx;
	this->sy=sy;
	this->sz=sz;
	this->p=p;
	#ifdef KEEP_ALL_LATTICE_IN_RAM
		this->r=new buffer(this->sx*this->sy*this->sz);
	#else
		this->r=new buffer(2*(this->sx*this->sy)+2);
	#endif
	this->bridges=new blist();
}

lattice::~lattice(){
	delete this->pointer;
	delete this->bridges;
	delete this->r;
}

int lattice::hkarbc(){
	#ifdef DEBUG
	std::clog << "@2\n";
	#endif
	#ifdef BENCHMARK
		this->time_scan=0;
	#endif	
	this->top_max=2;
	std::ofstream file;
	if(EXPORT){
		file.open("output.dat");
		file << this->sx << "\n" << this->sy << "\n" << this->sz << "\n";
	}
	#ifdef BENCHMARK
		time(&this->startt);
	#endif
	int max_id=2;
	#ifdef DEBUG
	std::clog << "@3\n";
	#endif
	//-------------------------------------------------------------------
	//Scan the first plane
	for(int y=0;y<this->sy;y++){
		for(int x=0;x<this->sx;x++){ // scan lattice in X-dir
			if(xrnd()<this->p){ // Cell occupied?
				if(x>0 && this->r->get()>0){
					// Take the value of his left neigbour if occupied
					*this->r << this->r->get();
				}
				else{
					// Take a new ID value
					*this->r << max_id;
				}
				//if(y>0) this->copyleft();
				//if(this->r->get()>this->top_max) this->top_max=this->r->get();
			}else{
				*this->r << 0; // Unoccupied cell
			}
		}
	}
	if(EXPORT){
		for(int x=(this->sy*this->sx)-1;x>=0;x--) file << this->r->get(x) << "\t";
		file << "\n";
	}
	#ifdef DEBUG
	std::clog << "@4\n";
	#endif
	//-------------------------------------------------------------------
	// Scan second plan
	for(int y=0;y<this->sy;y++){
		for(int x=0;x<this->sx;x++){ // scan lattice in X-dir
				if(xrnd()<this->p){ // Cell occupied?
					if(x>0 && this->r->get()>0){
						// Take the value of his left neigbour if occupied
						*this->r << this->r->get();
					}else{
						// Take a new ID value
						*this->r << ++max_id;
					}
					if(y>0) this->copyleft();
					this->copydown();
				}else{
					*this->r << 0; // Unoccupied cell
				}
				if(!CALCULATE_ONLY_PERCOL) this->lookbridge(x,y,1);
		}
	}
	if(EXPORT){
		for(int x=(this->sx*this->sy)-1;x>=0;x--) file << this->r->get(x) << "\t";
		file << "\n";
	}
	#ifdef DEBUG
	std::clog << "@5\n";
	#endif
	//----------------------------------------------------------------------------------------
	// Scan lattice
	for(int z=2;z<this->sz-1;z++){
		for(int y=0;y<this->sy;y++){  // Scan the lattice in Y-dir
			for(int x=0;x<this->sx;x++){ // scan lattice in X-dir
				if(xrnd()<this->p){ // Cell occupied?
					if(x>0 && this->r->get()>0){
						// Take the value of his left neigbour if occupied
						*this->r << this->r->get();
					}else{
						// Take a new ID value
						*this->r << ++max_id;
					}
					if(y>0) this->copyleft();
					this->copydown();
				}else{
					*this->r << 0; // Unoccupied cell
				}
				// Look for bridge
				if(!CALCULATE_ONLY_PERCOL) this->lookbridge(x,y,z);
			}
		}
		if(EXPORT){
			for(int x=(this->sy*this->sx)-1;x>=0;x--) file << this->r->get(x) << "\t";
			file << "\n";
		}
	}
	#ifdef DEBUG
	std::clog << "@6\n";
	#endif
	//-----------------------------------------------------------------------------------
	// Scan last plan
	int z=this->sz-1;
	list *end_id=new list();
	for(int y=0;y<this->sy;y++){
		for(int x=0;x<this->sx;x++){ // scan lattice in X-dir
			if(xrnd()<this->p){ // Cell occupied?
				if(x>0 && this->r->get()>0){
					// Take the value of his left neigbour if occupied
					*this->r << this->r->get();
				}else{
					// Take a new ID value
					*this->r << ++max_id;
				}
				if(y>0) this->copyleft();
				this->copydown();
				if(pointer->follow(this->r->get())<=this->top_max){
					#ifdef VERBOSE	
					std::clog << "*** PERCOLATE ***\n";
					#endif
					return -1; // PERCOLATE!!!
				}
				else end_id->add(this->r->get());
			}else{
				*this->r << 0; // Unoccupied cell
				if(this->r->get(this->sy*this->sx)>0 && pointer->follow(this->r->get(this->sy*this->sx))<=this->top_max){
					int v[]={1, this->r->get(this->sy*this->sx)};
					if(EXPORT){
						this->bridges->add(x,y,z,2,v);
					}else{
						this->bridges->add(2,v);
					}
				}
			}
			// Look for bridge
			if(!CALCULATE_ONLY_PERCOL) this->lookbridge(x,y,z);
		} // END FOR x
	} // END FOR Y
	if(EXPORT){
		for(int x=(this->sy*this->sx)-1;x>=0;x--) file << this->r->get(x) << "\t";
		file << "\n";
		file.close();
	}
	#ifdef DEBUG
	std::clog << "@7\n";
	#endif
	if(CALCULATE_ONLY_PERCOL) return 1;
	//----------------------------------------------------------------------------------------
	// End scanning
	if(BRIDGESINFO) std::clog << "#Bridges: " << this->bridges->num() << "\n";
	#ifdef BENCHMARK
		time(&this->endt);
		this->time_scan=difftime(this->endt,this->startt);
		std::clog << "Scan time: " << this->time_scan << "\n";
	#endif
	if(CALCULATE_ONLY_BRIDGES) return this->bridges->num();
	//=================================
	// Shortening
		pointer->shortening();
		int j=end_id->getlist();
		while(j>0){
			int kk=pointer->follow(j);
			pointer->set(kk,1);
			j=end_id->getlist();
		}
		if(EXPORT){
			pointer->write("pointer.dat");
		}
			
	//=================================
	int arb=this->bridges->scan(top_max, this->pointer);

	if(EXPORT){
		std::ofstream ff;
		ff.open("bridges.dat");
		this->bridges->write(ff);	
	}
	
	#ifdef BENCHMARK
		time(&this->startt);
		this->time_update=difftime(this->startt,this->endt);
		std::clog << "Bridges scan time: " << this->time_update << "\n";
	#endif
	delete end_id;
	return arb; 
}


