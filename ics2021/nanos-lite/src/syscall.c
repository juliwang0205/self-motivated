#include "syscall.h"
void do_syscall(Context *c) {
  //Log("do_syscall");
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  //Log(" c->GPR1 %d",  c->GPR1);
  //Log("%s %d\n", "SYS_exit", c->GPRx);
  switch (a[0]) {
    case SYS_exit:
      Log("SYS_exit");
      halt(0);
      c->GPRx = 0;
      break;

    case SYS_yield:
      Log("SYS_yield");
      yield(); 
      c->GPRx = 0;
      break;

    case SYS_write:
      //Log("SYS_write");
      //Log("a[1] = %d a[3] = %d", a[1], a[3]);
      c->GPRx = write(a[1], (void* )a[2], a[3]);
      break;

    default: panic("Do syscall Unhandled syscall ID = %d", a[0]); break;
  }
}
