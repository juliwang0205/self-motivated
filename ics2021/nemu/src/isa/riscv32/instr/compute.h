def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}

def_EHelper(addi) {
  rtl_addi(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(auipc) {
  rtl_addi(s, ddest, &s->pc, id_src1->imm);
}

def_EHelper(jal) {
  rtl_addi(s, ddest, &s->pc, 4);
  //ddest = &s->pc + 4;
  rtl_addi(s, &s->pc, &s->pc, id_src1->imm);
  //&s->pc += id_src1->imm;
  rtl_j(s, s->pc);
}

def_EHelper(jalr) {
  word_t tmp;
  rtl_addi(s, &tmp, &s->pc, 4);
  rtl_addi(s, &s->pc, id_src1->preg, id_src2->imm);
  rtl_li(s, ddest, tmp);
  rtl_j(s, s->pc);
}

