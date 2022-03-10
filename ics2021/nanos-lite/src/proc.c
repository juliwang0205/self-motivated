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
    Log("Hello World from Nanos-lite with arg '%p' for the %dth time!", (uintptr_t)arg, j);
    j ++;
    yield();
  }
}

void init_proc() {
  switch_boot_pcb();
  //naive_uload(NULL, "/bin/nterm");
  naive_uload(NULL, "/bin/bird");
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
  return NULL;
}
