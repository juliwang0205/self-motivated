#include <stdio.h>
#include <sys/time.h>
int main() {
	struct timeval tv;                                
	int temp = -1;                                     
	int t = -1;                                         
	while(1){                                         
	  gettimeofday(&tv, NULL);                        
	  t = tv.tv_usec;                                       
	  if(t / 500000 != temp) {                      
		temp = t / 500000;                    
		printf("0.5 sec pass!!! %d\n", temp);          
	  }                                               
	} 
  return 0;
}
