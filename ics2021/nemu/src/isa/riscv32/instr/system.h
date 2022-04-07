def_EHelper(csrrs){
  switch(id_src2->imm){
    case 0x340:
      dsrc2 = &(cpu.mscratch);
      break;
    case 0x341:
      dsrc2 = &(cpu.mepc);
      break;
    case 0x342:
      dsrc2 = &(cpu.mcause);
      break;
    case 0x300:
      dsrc2 = &(cpu.mstatus.value);
      break;
    case 0x305:
      dsrc2 = &(cpu.mtvec);
      break;
    case 0x180:
      dsrc2 = &(cpu.satp);
      break;
    default:
      assert(0);
  }
  rtl_addi(s, ddest, dsrc2, 0);
  rtl_or(s, dsrc2, dsrc1, dsrc2);
}

def_EHelper(csrrw){
  switch(id_src2->imm){
    case 0x340:
      dsrc2 = &(cpu.mscratch);
    case 0x341:
      dsrc2 = &(cpu.mepc);
      break;
    case 0x342:
      dsrc2 = &(cpu.mcause);
      break;
    case 0x300:
      dsrc2 = &(cpu.mstatus.value);
      break;
    case 0x305:
      dsrc2 = &(cpu.mtvec);
      break;
    case 0x180:
      dsrc2 = &(cpu.satp);
      break;
    default:
      assert(0);
  }
  rtl_addi(s, ddest, dsrc2, 0);
  rtl_addi(s, dsrc2, dsrc1, 0);
}


#define Machine_Software_Interrupt (11)
#define User_Software_Interrupt (8)
def_EHelper(ecall){
  //a7 refs for cpu.gpr[17]._32, a2 stand for mcause NO
  //isa_raise_intr(cpu.gpr[17]._32, cpu.pc);
  if(cpu.mstatus.m.MPP == 3) {
    isa_raise_intr(Machine_Software_Interrupt, cpu.pc);
  }else if(cpu.mstatus.m.MPP == 0) {
    isa_raise_intr(User_Software_Interrupt, cpu.pc);
  }else {
    assert(0);
  }
  rtl_j(s, cpu.mtvec);
}

def_EHelper(mret) {
  cpu.mstatus.m.MIE = cpu.mstatus.m.MPIE;
  cpu.mstatus.m.MPIE = 1;
  rtl_j(s, cpu.mepc);
}
