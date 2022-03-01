#include <stdio.h>
#include <sys/time.h>
#include <NDL.h>
int main() {
	//struct timeval tv;
  int temp = -1;
  int t = -1;
  NDL_Init(0);
	while(1){
    /*
	  gettimeofday(&tv, NULL);                        
	  t = tv.tv_usec;                                       
	  if(t / 500000 != temp) {                      
		  temp = t / 500000;
		  printf("0.5 sec pass!!! %d\n", temp);
	  }
    */
    t = NDL_GetTicks();
    if(t / 500 != temp) {
      temp = t / 500;
      printf("0.5 sec pass!!! %d\n", temp);
    }
	} 
  return 0;
}
