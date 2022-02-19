#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(inv) f(nemu_trap) \
  f(addi) f(slti) f(sltiu) f(xori) f(ori) f(andi) f(slli) f(srli) f(srai)\
  f(auipc) f(jal) f(jalr)\
  f(beq) f(bne) f(blt) f(bge) f(bltu) f(bgeu) \
  f(sb) f(sh) f(sw) f(sd) \
  f(lb) f(lbu) f(lh) f(lhu) f(lw)f(lwu) f(ld) \
  f(add) f(sub) f(div) f(divu) f(mul) f(mulh) f(mulhsu) f(mulhu) f(rem) f(remu)\
  f(sll) f(slt) f(sltu)f(xor) f(srl) f(sra) f(or) f(and) \
  f(csrrw) f(ecall) f(csrrs) f(mret) //f(sret) f(sfence_vma)

def_all_EXEC_ID();
