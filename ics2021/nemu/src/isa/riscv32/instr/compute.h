def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
  //Log("\nlui: ");
  //isa_reg_display();
}

def_EHelper(addi) {
  rtl_addi(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(slti) {
  rtl_setrelopi(s, RELOP_LT, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(sltiu) {
  rtl_setrelopi(s, RELOP_LTU, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(xori) {
  rtl_xori(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(ori) {
  rtl_ori(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(andi) {
  rtl_andi(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(slli) {
  rtl_slli(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(srli) {
  rtl_srli(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(srai) {
  rtl_srai(s, ddest, id_src1->preg, id_src2->imm);
}

def_EHelper(auipc) {
  rtl_addi(s, ddest, &s->pc, id_src1->imm);
}

def_EHelper(jal) {
  rtl_li(s, ddest, 4 + s->pc);
  rtl_j(s, s->pc + id_src1->imm);
}

def_EHelper(jalr) {
  rtl_j(s, *dsrc1 + id_src2->imm);
  rtl_li(s, ddest, 4 + s->pc);
}

def_EHelper(add) {
  rtl_add(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sub) {
  rtl_sub(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mul) {
  rtl_mulu_lo(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mulh) {
  rtl_muls_hi(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mulhsu) {
  rtl_mulu_hi(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(mulhu) {
  rtl_mulu_hi(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(div) {
  rtl_divs_q(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(divu) {
  rtl_divu_q(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(rem) {
  rtl_divs_r(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(remu) {
  rtl_divu_r(s, ddest, id_src1->preg, id_src2->preg);
}



def_EHelper(sll) {
  rtl_sll(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(slt) {
  rtl_setrelop(s, RELOP_LT, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sltu) {
  rtl_setrelop(s, RELOP_LTU, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(xor) {
  rtl_xor(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(srl) {
  rtl_srl(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(sra) {
  rtl_sra(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(or) {
  rtl_or(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(and) {
  rtl_and(s, ddest, id_src1->preg, id_src2->preg);
}

def_EHelper(beq) {
  rtl_jrelop(s, RELOP_EQ, id_src1->preg, id_src2->preg, id_dest->imm);
}

def_EHelper(bne) { 
  rtl_jrelop(s, RELOP_NE, id_src1->preg, id_src2->preg, id_dest->imm);
}

def_EHelper(blt) { 
  rtl_jrelop(s, RELOP_LT, id_src1->preg, id_src2->preg, id_dest->imm);
}

def_EHelper(bge) {
  rtl_jrelop(s, RELOP_GE, id_src1->preg, id_src2->preg, id_dest->imm);
}

def_EHelper(bltu) { 
  rtl_jrelop(s, RELOP_LTU, id_src1->preg, id_src2->preg, id_dest->imm);
}

def_EHelper(bgeu) {
  rtl_jrelop(s, RELOP_GEU, id_src1->preg, id_src2->preg, id_dest->imm);
}




