#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  uint16_t idx = 0;
  for(idx= 0; idx < 32; idx++) {
    printf("reg %s data 0x%08x\n", regs[idx], gpr(idx));
  }
}

word_t isa_reg_str2val(const char *s, bool *success) {
  int idx;                    
  for (idx = 0; idx < 32; idx++) {
    if(!strcmp(regs[idx],s)){
      *success = true; 
      return gpr(idx);
    }
  }
  return 0;
}
