#include <proc.h>
#include <fs.h>

#define MAX_NR_PROC 4

extern void naive_uload(PCB *pcb, const char *filename);
static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%s' for the %dth time!", (char *)arg, j);
    j ++;
    yield();
  }
}

void context_kload(PCB *pcb, void (*entry)(void *), void *arg) {
  Area  karea;
  karea.start = &pcb->cp;
  karea.end   = &pcb->cp + STACK_SIZE;
  pcb->cp = kcontext(karea, entry, arg);
}

void init_proc() {
  context_kload(&pcb[0], hello_fun, "first");
  context_kload(&pcb[0], hello_fun, "second");
  switch_boot_pcb();
  //naive_uload(NULL, "/bin/nterm");
  //naive_uload(NULL, "/bin/bird");
  Log("Initializing processes...");

  // load program here

}

int execve(const char *fname, char * const argv[], char *const envp[]){
  if(fs_open(fname, 0 , 0) == -1)
   Log("%s cannot be found", fname);

  naive_uload(NULL, fname);
  return 0;
}

Context* schedule(Context *prev) {
  // dave the context pointer
  current->cp = prev;
  // always select pcb[0] as the new process
  current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
  // return the new context
  return current->cp;
}
