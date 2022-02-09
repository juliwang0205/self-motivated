#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  assert(s != NULL);
  size_t i = 0;
  while(s[i] !=  '\0') i++;
  return i; 
}

char *strcpy(char *dst, const char *src) {
  assert(dst!=NULL && src!=NULL);
  size_t i;
  for(i = 0; src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  assert(dst!=NULL && src!=NULL);
  assert(n >= 0);
  size_t i;
  for(i = 0; i < n && src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  assert(dst!=NULL && src!=NULL);
  char *str = dst;
  while(*dst != '\0') dst++;
  while(*src != '\0') *dst++ = *src++;
  *dst = '\0';
  return str;
}

int strcmp(const char *s1, const char *s2) {
  assert(s1 != NULL && s2 != NULL);
  size_t i;
  for(i = 0; s1[i] == s2[i]; i++){
    if(s1[i] == '\0') 
      return 0;
  }
  return(((int8_t*)s1)[i] -((int8_t*)s2)[i]);
}

int strncmp(const char *s1, const char *s2, size_t n) {
  assert(s1 != NULL && s2 != NULL);
  assert(n >= 0); 
  size_t i;
  for(i = 0; i < n && s1[i] == s2[i]; i++){
    if(s1[i] == '\0') 
      return 0;
  }
  return(((int8_t*)s1)[i] -((int8_t*)s2)[i]);
}

void *memset(void *s, int c, size_t n) {
  assert(s != NULL);
  assert(n >= 0);
  const unsigned char uc = c; /* only cat the lowest c */
  unsigned char *vu;
  for (vu = s; 0 < n; ++vu, --n)
	  *vu = uc;
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  assert( dst != NULL && src != NULL);
  assert(n >= 0);
  size_t i ;
  if(dst < src) {
    while (n--) *((char *)dst++) = *((char *)src++);
  }
  else {
    for(i = n; i > 0; i--)
      *((char *)dst + n) = *((char *)src + n);
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  assert(out != NULL && in != NULL);
  assert(n >= 0); 
  const char *src = in;
  char *dst = out;
  while (n--) *dst++ = *src++;
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  assert(s1 != NULL && s2 != NULL);
  assert(n >= 0); 
  if(!n) return 0;
  while(--n && *(char *)s1 == *(char *)s2) {
	  s1 = (char *)s1 + 1;
	  s2 = (char *)s2 + 1;
  }
  return (*((unsigned char *)s1) - *((unsigned char *)s2));
}

#endif
