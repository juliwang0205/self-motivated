#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(nemu_trap) \
  f(addi) f(auipc) f(jal) f(jalr) f(add) f(sub) f(sltiu) f(bne) \
  f(beq) f(sltu) f(xor) f(or)
def_all_EXEC_ID();
