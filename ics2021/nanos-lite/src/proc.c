#include <proc.h>
#include <fs.h>
#include <load.h>

//extern void naive_uload(PCB *pcb, const char *filename);
//extern void context_kload(PCB *pcb, void (*entry)(void *), void *arg);
//extern void context_uload(PCB *pcb, const char *filename, char *const argv[], char *const envp[]);
#define MAX_NR_PROC 4

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

void init_proc() {
  context_kload(&pcb[0], hello_fun, "first");
  //context_kload(&pcb[1], hello_fun, "second");
  context_uload(&pcb[1], "/bin/bird", NULL, NULL);
  switch_boot_pcb();
  //naive_uload(NULL, "/bin/nterm");
  //naive_uload(NULL, "/bin/bird");
  Log("Initializing processes...");

  // load program here

}

int execve(const char *fname, char * const argv[], char *const envp[]){
  if(fs_open(fname, 0 , 0) == -1)
   Log("%s cannot be found", fname);

  Log("loading %s", fname);
  context_uload(&pcb[1], fname, argv, envp);
  switch_boot_pcb();
  
  yield();
  //naive_uload(NULL, fname);
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
