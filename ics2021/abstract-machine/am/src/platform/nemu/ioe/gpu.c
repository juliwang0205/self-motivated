#include <am.h>
#include <nemu.h>
#include <klib.h>
#include <amdev.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

static inline int min(int x, int y) {
  return (x < y) ? x : y;
}

void __am_gpu_init() {
	/*int i;
	int w = 128;  // TODO: get the correct width
	int h = 128;  // TODO: get the correct height
	uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
	for (i = 0; i < w * h; i ++) fb[i] = i;
	outl(SYNC_ADDR, 1);
  */
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 400, .height = 300,
    .vmemsz = 0
  };
}

#define W 400
#define H 300

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  uint32_t *pixels = ctl->pixels;
//  int W = io_read(AM_GPU_CONFIG).width;
//  int H = io_read(AM_GPU_CONFIG).height;
//  int cp_bytes = sizeof(uint32_t) * min(w, W - x);
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  //for (int j = 0; j < h && y + j < H; j++){
  //  memcpy(&fb[(y + j) * W + x], pixels, cp_bytes);
  //  pixels += w;
  //}

  int len = sizeof(uint32_t)*((x+w<W)?w:W-x);
  for(int i=0;i<h&&i+y<H;++i){
    memcpy(&fb[(i+y)*W+x],pixels+i*w,len);
  }
  outl(SYNC_ADDR, 1);
  if (ctl->sync) {
//    outl(SYNC_ADDR, 0);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
