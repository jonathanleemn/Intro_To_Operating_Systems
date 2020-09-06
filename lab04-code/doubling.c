#include <stdio.h>

int main(){
  long iters = 1;
  while(1){
    for(long i=0; i < iters; i++){
      printf("X");
    }
    printf("\n");
    //    fflush(stdout);
    iters = iters << 1;
  }
  return 0;
}
