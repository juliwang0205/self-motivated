#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    switch (c->GPR1) {
      case -1:ev.event = EVENT_YIELD;break;//yield
      case  0: case  1:  case 2: case  3: case  4: case  5: case  6: case 7: case   8: case 9:
      case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
               ev.event = EVENT_SYSCALL; break;
      default: ev.event = EVENT_ERROR;   break;
    }
    c = user_handler(ev, c); // --> do_event
    assert(c != NULL);
  }
#ifdef CONFIG_ETRACE
  printf("raise exception no.%u\n", ev.event);
#endif
  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler; // -->do_event

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  // change -1 to 0 to call sys_exit
  asm volatile("li a7, 0; ecall");
}

int write(int fd, void *buf, size_t count)
{
  int ret = 0;
  char *str = (char *)buf;
  if(fd == 1 || fd == 2) {
    for(size_t i = 0; i < count; i ++) {
      putch(str[i]);
      ret++;
    }
  }
  return ret;
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
