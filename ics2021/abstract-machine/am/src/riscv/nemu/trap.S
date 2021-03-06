#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define MAP(c, f) c(f)

#if __riscv_xlen == 32
#define LOAD  lw
#define STORE sw
#define XLEN  4
#else
#define LOAD  ld
#define STORE sd
#define XLEN  8
#endif

#define REGS(f) \
      f( 1)       f( 3) f( 4) f( 5) f( 6) f( 7) f( 8) f( 9) \
f(10) f(11) f(12) f(13) f(14) f(15) f(16) f(17) f(18) f(19) \
f(20) f(21) f(22) f(23) f(24) f(25) f(26) f(27) f(28) f(29) \
f(30) f(31)

#define PUSH(n) STORE concat(x, n), (n * XLEN)(sp);
#define POP(n)  LOAD  concat(x, n), (n * XLEN)(sp);

#define CONTEXT_SIZE  ((32 + 3 + 1) * XLEN)
#define OFFSET_SP     ( 2 * XLEN)
#define OFFSET_CAUSE  (32 * XLEN)
#define OFFSET_STATUS (33 * XLEN)
#define OFFSET_EPC    (34 * XLEN)

.align 3
.globl __am_asm_trap
__am_asm_trap:
  addi sp, sp, -CONTEXT_SIZE # sp stack pointer move to sp = sp-CONTEXT_SIZE to store register data

  MAP(REGS, PUSH)            # push all the register's data into stack

  csrr t0, mcause            # move mcause to t0
  csrr t1, mstatus           # move mstatus to t1
  csrr t2, mepc              # move mepc to t2

  STORE t0, OFFSET_CAUSE(sp) # push t0 to stack
  STORE t1, OFFSET_STATUS(sp)# push t1 to stack
  STORE t2, OFFSET_EPC(sp)   # push t2 to stack

  # set mstatus.MPRV to pass difftest
  li a0, (1 << 17)
  or t1, t1, a0
  csrw mstatus, t1

  mv a0, sp                  # a0 store sp
  jal __am_irq_handle        # jump to __am_irq_handle

  mv sp, a0

  LOAD t1, OFFSET_STATUS(sp) # pop mstatus to t1
  LOAD t2, OFFSET_EPC(sp)    # pop mepc to t2
  csrw mstatus, t1           # pop mstatus to t1
  
  addi t2, t2, 4             # mepc add 4 to mepc(pc+4) (after ecall instr pc+4)
  csrw mepc, t2              # pop mepc to t2
  addi t2, t2, -4            # restore pc

  MAP(REGS, POP)             # pop all the register

  addi sp, sp, CONTEXT_SIZE  # restore sp pointer
  mret                       # restore from expection
