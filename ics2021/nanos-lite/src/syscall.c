#include <common.h>
#include "syscall.h"
#include <device.h>
#include <fs.h>

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
      Log("SYS_write");
      //for standard in/out (call in cte.c)
      //c->GPRx = write(a[1], (void* )a[2], a[3]);
      c->GPRx = fs_write(a[1], (void* )a[2], a[3]);
      break;
    case SYS_read:
      Log("SYS_read");
      c->GPRx = fs_read(a[1], (void* )a[2], a[3]);
      break;
    case SYS_open:
      Log("SYS_open");
      c->GPRx = fs_open((const char* )a[1], a[2], a[3]);
      break;
    case SYS_lseek:
      Log("SYS_lseek");
      c->GPRx = fs_lseek(a[1], a[2], a[3]);
      break;
    case SYS_close:
      Log("SYS_close");
      c->GPRx = fs_close(a[1]);
      break;
    case SYS_brk:
      Log("SYS_brk");
      c->GPRx = 0;
      break;
    case SYS_gettimeofday:
      //Log("SYS_gettimeofday");
      c->GPRx = sys_gettimeofday((struct timeval*)a[1], (struct timezone*)a[2]);
      break;

    default: panic("Do syscall Unhandled syscall ID = %d", a[0]); break;
  }
}
