#include <memory.h>
#include <load.h>
#include <proc.h>
#include <elf.h>
#include <fs.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

static uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
  uint16_t i;
  uint16_t fd;
  Elf_Ehdr ehdr;
  fd = fs_open(filename, 0 , 0);
  fs_read(fd, &ehdr, sizeof(Elf_Ehdr));
  //ramdisk_read(&ehdr, 0, sizeof(Elf_Ehdr));
  //check elf file E='45' L='4c' F='46'
  assert(*(uint32_t *)ehdr.e_ident == 0x464c457f);
  //check CPU type EM_RISCV stand for riscv see /usr/include/elf.h to get the right type
  assert(ehdr.e_machine == EM_RISCV);
  Elf_Phdr phdr[ehdr.e_phnum];
  fs_lseek(fd, ehdr.e_ehsize, SEEK_SET);
  fs_read(fd, phdr, sizeof(Elf_Phdr) * ehdr.e_phnum);
  //ramdisk_read(phdr, ehdr.e_ehsize, sizeof(Elf_Phdr) * ehdr.e_phnum);
  for(i = 0; i < ehdr.e_phnum; i++) {
    if(phdr[i].p_type == PT_LOAD) {
      fs_lseek(fd, phdr[i].p_offset, SEEK_SET);
      fs_read(fd, (void *)phdr[i].p_vaddr, phdr[i].p_memsz);
      //ramdisk_read((void *)phdr[i].p_vaddr, phdr[i].p_offset, phdr[i].p_memsz);
      memset((void *)(phdr[i].p_vaddr + phdr[i].p_filesz), 0 , phdr[i].p_memsz - phdr[i].p_filesz);
    }
  }
  fs_close(fd);
  return ehdr.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = 0x%x", entry);
  ((void(*)())entry) ();
}

static size_t ceil_4_bytes(size_t size) {
  if(size & 0x03)
    return (size & ~0x03) + 4;
  return size;
}

void context_kload(PCB *pcb, void (*entry)(void *), void *arg) {
  Area  karea;
  karea.start = &pcb->cp;
  karea.end   = &pcb->cp + STACK_SIZE;
  pcb->cp     = kcontext(karea, entry, arg);
}

#define NR_PAGE 8
void context_uload(PCB *pcb, const char *filename, char *const argv[], char *const envp[]) {
  Area karea;
  int argc = 0, envc = 0;
  if(argv) {
    for(; argv[argc]; ++argc){}
  }
  if(envp) {
    for(; envp[envc]; ++envc){}
  }
  
  void *allocated_pages = new_page(NR_PAGE) + NR_PAGE * 4096;
  char *brk = (char *)(allocated_pages - 4);

/* stack info
  |               |
  +---------------+ <---- ustack.end
  |  Unspecified  |
  +---------------+
  |               | <----------+
  |    string     | <--------+ |
  |     area      | <------+ | |
  |               | <----+ | | |
  |               | <--+ | | | |
  +---------------+    | | | | |
  |  Unspecified  |    | | | | |
  +---------------+    | | | | |
  |     NULL      |    | | | | |
  +---------------+    | | | | |
  |    ......     |    | | | | |
  +---------------+    | | | | |
  |    envp[1]    | ---+ | | | |
  +---------------+      | | | |
  |    envp[0]    | -----+ | | |
  +---------------+        | | |
  |     NULL      |        | | |
  +---------------+        | | |
  | argv[argc-1]  | -------+ | |
  +---------------+          | |
  |    ......     |          | |
  +---------------+          | |
  |    argv[1]    | ---------+ |
  +---------------+            |
  |    argv[0]    | -----------+
  +---------------+
  |      argc     |
  +---------------+ <---- cp->GPRx
  |               |
*/
  //copy envp to envp_ustack 
  char *envp_ustack[envc];  
  for(int i = 0; i < envc; i ++) {
    brk -= ceil_4_bytes(strlen(envp[i] + 1));
    envp_ustack[i] = brk;
    strcmp(brk, envp[i]);
  }
  //copy argv to argv_ustack  
  char *argv_ustack[argc];
  for(int i = 0; i < argc; i++) {
    brk -= ceil_4_bytes(strlen(argv[i] + 1));
    argv_ustack[i] = brk;
    strcmp(brk, argv[i]);
  }

  intptr_t *ptr_brk = (intptr_t *) brk;
  // allocate envp stack to store envp info
  ptr_brk -= 1;
  *ptr_brk = 0;
  ptr_brk -= envc;
  for(int i = 0; i < envc; i++){
    ptr_brk[i] = (intptr_t)envp_ustack[i]; 
  }

  // allocate argv stack to store argv info
  ptr_brk -= 1;
  *ptr_brk = 0;
  ptr_brk -= argc;
  for(int i = 0; i < argc; i++) {
    ptr_brk[i] = (intptr_t)argv_ustack[i];
  }

  // store argc to stcre argc
  ptr_brk -= 1;
  *ptr_brk = argc;

  // this instuction will store the paramters in the last
  uintptr_t entry = loader(pcb, filename);
  karea.start  = &pcb->cp;
  karea.end    = &pcb->cp + STACK_SIZE;
  Context *cte = ucontext(&pcb->as, karea, (void *)entry);
  pcb->cp      = cte;

  // GPRx point to argc address
  cte->GPRx    = (uintptr_t)ptr_brk; 
}
