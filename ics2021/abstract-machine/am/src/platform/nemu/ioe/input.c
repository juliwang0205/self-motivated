#include <am.h>
#include <nemu.h>
#include <../../../riscv/riscv.h>
#include <klib.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t kbd_data = inl(KBD_ADDR);
  kbd->keydown = (kbd_data & KEYDOWN_MASK) ? 1 : 0;
  kbd->keycode = (kbd_data!=0) ? kbd_data : AM_KEY_NONE;
}
