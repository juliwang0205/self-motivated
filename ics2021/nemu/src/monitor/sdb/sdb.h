#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

word_t expr(char *e, bool *success);

typedef struct watchpoint {
  int NO;
  /*watchpoint name*/
  char exp[32];
  /*watchpoint value*/
  uint32_t value;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */

} WP;

WP* new_wp(char * exp);
bool delete_wp(int num);
void print_wp();
#endif
