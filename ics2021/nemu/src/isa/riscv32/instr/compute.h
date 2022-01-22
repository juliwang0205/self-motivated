def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
  //Log("\nlui: ");
  //isa_reg_display();
}

def_EHelper(addi) {
  rtl_addi(s, ddest, id_src1->preg, id_src2->imm);
  //Log("\naddi: ");
  //isa_reg_display();
}

def_EHelper(auipc) {
  rtl_addi(s, ddest, &s->pc, id_src1->imm);
  //Log("\nauipc: ");
  //isa_reg_display();
}

def_EHelper(jal) {
  rtl_li(s, ddest, s->snpc);
  //rtl_j(s, id_src1->imm);
  rtl_addi(s, &s->pc, &s->pc, id_src1->imm);
  rtl_j(s, s->pc);

  //Log("\njal: ");
  //isa_reg_display();
}

def_EHelper(jalr) {
  rtl_li(s, ddest, s->snpc);
  rtl_addi(s, &s->pc, id_src1->preg, id_src2->imm);
  rtl_j(s, s->pc);
  //Log("\njalr: ");
  //isa_reg_display();
}

def_EHelper(sltiu) {
  rtl_setrelopi(s, RELOP_LTU, ddest, id_src1->preg, id_src2->imm);
  //Log("\nstlui: ");
  //isa_reg_display();
}

def_EHelper(add) {
  rtl_add(s, ddest, id_src1->preg, id_src2->preg);
  //Log("\nadd: ");
  //isa_reg_display();
}

def_EHelper(sub) {
  rtl_sub(s, ddest, id_src1->preg, id_src2->preg);
  //Log("\nsub: ");
  //isa_reg_display();
}

def_EHelper(bne) { 
  rtl_jrelop(s, RELOP_NE, id_src1->preg, id_src2->preg, id_dest->imm);
  //Log("\nbne: ");
  //isa_reg_display();
}

def_EHelper(beq) {
  rtl_jrelop(s, RELOP_EQ, id_src1->preg, id_src2->preg, id_dest->imm);
  //Log("\nbeq: ");
  //isa_reg_display();
}

def_EHelper(sltu) {
  rtl_setrelop(s, RELOP_LTU, ddest, id_src1->preg, id_src2->preg); 
}

def_EHelper(xor) {
  rtl_xor(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(or) {
  rtl_or(s, ddest, id_src1->preg, id_src2->preg);
}
