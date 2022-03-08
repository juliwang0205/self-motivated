#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"
#include <memory/paddr.h>
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  uint16_t idx;
  
  for(idx = 0; idx < 32; idx++) {
    if(ref_r->gpr[idx]._32 != gpr(idx))
      return false;
  }
  return true;
}

void isa_difftest_attach() {
  ref_difftest_memcpy(CONFIG_MBASE, guest_to_host(CONFIG_MBASE), CONFIG_MSIZE, DIFFTEST_TO_REF);
  ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}
