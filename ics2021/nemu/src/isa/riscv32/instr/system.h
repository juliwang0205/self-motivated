def_EHelper(csrrs){
  switch(id_src2->imm){
    case 0x341:
      dsrc2 = &(cpu.mepc);
      break;
    case 0x342:
      dsrc2 = &(cpu.mcause);
      break;
    case 0x300:
      dsrc2 = &(cpu.mstatus);
      break;
    case 0x305:
      dsrc2 = &(cpu.mtvec);
      break;
  }
  rtl_addi(s, ddest, dsrc2, 0);
  rtl_or(s, dsrc2, dsrc1, dsrc2);
}

def_EHelper(csrrw){
  switch(id_src2->imm){
    case 0x341:
      dsrc2 = &(cpu.mepc);
      break;
    case 0x342:
      dsrc2 = &(cpu.mcause);
      break;
    case 0x300:
      dsrc2 = &(cpu.mstatus);
      break;
    case 0x305:
      dsrc2 = &(cpu.mtvec);
      break;
  }
  rtl_addi(s, ddest, dsrc2, 0);
  rtl_addi(s, dsrc2, dsrc1, 0);
}

def_EHelper(ecall){
  //a7 refs for cpu.gpr[17]._32, a2 stand for mcause NO
  isa_raise_intr(cpu.gpr[17]._32, cpu.pc);
  rtl_j(s, cpu.mtvec);
}

def_EHelper(mret) {
  rtl_j(s, cpu.mepc);
}