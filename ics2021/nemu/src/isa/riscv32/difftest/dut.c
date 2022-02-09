#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  uint16_t idx;
  
  for(idx = 0; idx < 32; idx++) {
    if(ref_r->gpr[idx]._32 != gpr(idx))
      return false;
  }
  return true;
}

void isa_difftest_attach() {
}
