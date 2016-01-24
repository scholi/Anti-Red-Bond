/* #############################################
 * #    Anti Red-Bond calculation algorithm    #
 * #############################################
 *
 * File Version: 1.0
 * Date: 05 june 2008
 * License: GPL (http://gnu.org/licenses/gpl.html)
 * Author: Olivier Scholder <oliviesc@phys.ethz.ch>
 * Description:	see the man page (file: ../doc/arb.man)
 * 		to see the manpage without installing it:
 * 		groff -Tascii -man arb.man | less
 */

#include "lattice3d.h"
#include "stat.h"
#include <iostream>
#include <ctime>
#include <getopt.h>

extern char *optarg;
extern int optind, opterr;

bool CALCULATE_ONLY_PERCOL=false;
bool CALCULATE_ONLY_BRIDGES=false;
bool BRIDGESINFO=false;
bool EXPORT=false;

int main(int argc, char *argv[]){
	
	int size=10;
	double p=0.3116081;
	int n=1;
	bool d2=false;

	int c;
	static char optstring[] = "L:d:n:psbBe";
	while((c=getopt(argc, argv, optstring)) != -1){
		switch(c){
			case 'L':
				size=atoi(optarg);
				break;
			case 'd':
				p=atof(optarg);
				break;
			case 'p':
				CALCULATE_ONLY_PERCOL=true;
				break;
			case 'n':
				n=atoi(optarg);
				break;
			case 's':
				d2=true;
				break;
			case 'b':
				BRIDGESINFO=true;
				break;
			case 'B':
				CALCULATE_ONLY_BRIDGES=true;
				break;
			case 'e':
				EXPORT=true;
				break;
			case '?':	
				std::cout << "Found an invalid argument!\n";
				exit(1);
		}
	}
	srand(time(0));
	lattice *l;
	stat st;
	if(!CALCULATE_ONLY_PERCOL){
		if(n==1){
			int ar=-1;
			while(ar<0){
				if(d2){
					l=new lattice(size,1,size,p);
				}else{
					l=new lattice(size,size,size,p);
				}
				ar=l->hkarbc();
				delete l;
			}
			std::cout << size << "\t" << p << "\t" << ar << "\n";
		}else{
			for(int s=0; s<n; s++){
				int ar=-1;
				while(ar<0){
					if(d2){
						l=new lattice(size,1,size,p);
					}else{
						l=new lattice(size,size,size,p);
					}
					ar=l->hkarbc();
					delete l;
				}
				st << ar;
				std::clog << size << "\t" << p << "\t" << ar << "\n";
			}
			std::cout << size << "\t" << p << "\t" << st.mean() << "\t" << st.err() << "\n";
		}
	}else{
		int per=0;
		for(int i=0;i<n;i++){
			if(d2){
				l=new lattice(size,1,size,p);
			}else{
				l=new lattice(size,size,size,p);
			}
			int ar=l->hkarbc();
			if(ar==-1){
				st << 1;
				//std::clog << "PERCOL\n";
			}
			else{
				st << 0;
				//std::clog << "OK\n";
			}
			delete l;
		}
		std::cout << size << "\t" << p << "\t" << st.mean() << "\t" << st.err() << "\n";
	}
	return 0;
}
