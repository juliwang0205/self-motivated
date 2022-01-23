#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

char* get_ch(char *dest, int num, int n) {
	char number[20];
	for (int j=0;j<10;j++) {number[j]=j+'0';}
	number[10] = 'a'; number[11] = 'b'; number[12] = 'c'; number[13] = 'd'; number[14] = 'e'; number[15] = 'f';
	int l=0;
	int flag=0;
	if(num==0) {
		dest[0]='0';
		dest[1]='\0';
		return dest;
	}
	if(num<0) {
		flag=1;
		l++;
		num=-num;
	}
	int temp=num;
	while(temp>0) {
		l++;
		temp=temp/n;
	}
	for (int a=0; a<l; a++) {
		int x=num%n;
		assert(x<16);
		dest[l-a-1]=number[x];
		num=num/n;
	}
	if(flag) {dest[0]='-';}
	dest[l]='\0';
	return dest;
}

int printf(const char *format, ...) {
  panic("Not implemented"); 
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  int sum=0;
  int i=0;
  int len=strlen(fmt);
  out[0]='\0';
  while(i<len) {
    if(fmt[i]=='%') {
      int num=0;
      char ls[50]="";
      switch(fmt[i+1]) {
        case 'd': {
	  		num=va_arg(ap,int);
	  		get_ch(ls, num, 10);
	  		strcat(out,ls);
	  		sum+=strlen(ls);	
        } break;
		case 's': {
	  		strcpy(ls,va_arg(ap, char*));
	  		strcat(out,ls);
	  		sum += strlen(ls);
		} break;
		default: {
			printf("sprintf fault \n");
		}
	  } 
      i+=2;
	}
    else {
      	sum++;
      	char s[2];
      	s[0]=fmt[i];
      	s[1]='\0';
      	strcat(out,s);
      	i++;
  	}
 }
  va_end(ap);
  return sum; 
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
