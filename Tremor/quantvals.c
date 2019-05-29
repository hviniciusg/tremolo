#include <stdio.h>
#include <limits.h>
#include "codebook.h"
#include <stdlib.h>

int _ilog(unsigned int v){
  int ret=0;
  while(v){
    ret++;
    v>>=1;
  }
  return(ret);
}

long _book_maptype1_quantvals(long entries,long dim){
  /* get us a starting hint, we'll polish it below */
  int bits=_ilog(entries);
  int vals=entries>>((bits-1)*(dim-1)/dim);

  while(1){
    long acc=1;
    long acc1=1;
    int i;
    for(i=0;i<dim;i++){
      acc*=vals;
      acc1*=vals+1;
    }
    if(acc<=entries && acc1>entries){
      return(vals);
    }else{    
      if(acc>entries){
        vals--;
      }else{
        vals++;
      }
    }
  }
}

long p_book_maptype1_quantvals(long entries,long dim){
  /* get us a starting hint, we'll polish it below */
  int bits=_ilog(entries);
  int vals=entries>>((bits-1)*(dim-1)/dim);

  while(1){
    long acc=1;
    long acc1=1;
    int i;
    for (i = 0; i < dim; i++) {
      if (acc > entries / vals) {
          break;
      }
      acc *= vals;
      if (acc1 > LONG_MAX / (vals + 1)) {
        acc1 = LONG_MAX;
      } else {
        acc1 *= (vals + 1);
  	}
    }
    if (i >= dim && acc <= entries && acc1 > entries) {
      return(vals);
    }else{
      if (i < dim || acc > entries) {
        vals--;
      }else{
        vals++;
      }	
    }
  }
}


long getRandomBits(int length){
 return rand() % (1<<length);
}


int main( int argc, const char* argv[] ){	
	int i,j;
	codebook *s;
	codebook p = {.q_bits = 32, .dim=0, .entries=0};
	s = &p;

	printf("program started \n");
	for(i=1;i<=100;i++){
		for(j=1;j<=100;j++){
			int quantvals1 = _book_maptype1_quantvals(i,j);
			int quantvals2 = p_book_maptype1_quantvals(i,j);
			printf("dim:%i, entries:%i, Quantval: %i , P Quantval: %i \n",i,j,quantvals1,quantvals2);
		}		
	}
}

