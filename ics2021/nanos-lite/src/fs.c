#include <device.h>
#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t current;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, serial_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, serial_write},
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
}

size_t lenchoose(size_t a, size_t b) {
  return a <= b ? a : b;
}

int fs_open(const char *pathname, int flags, int mode) {
  size_t fileNum = sizeof(file_table) / sizeof(Finfo);
  size_t i = 0;
  for(i = 0; i < fileNum; i++) {
    if(strcmp(file_table[i].name, pathname) == 0) {
      Log("fs_open file name %s",file_table[i].name);
      file_table[i].current = 0;
      return i;
    }
  }
  Log("cannot find %s",pathname);
  assert(i!=fileNum);
  return -1;
}

size_t fs_read(int fd, void *buf, size_t len) {
  size_t ret  = -1;
  size_t readlen = lenchoose(len, file_table[fd].size - file_table[fd].current);
  assert(readlen + file_table[fd].current <= file_table[fd].size);
  size_t offset = file_table[fd].disk_offset + file_table[fd].current;
  if(file_table[fd].read == NULL) {
    ret = ramdisk_read(buf, offset, readlen);
    file_table[fd].current += readlen;
  }
  else {
    ret = file_table[fd].read(buf, offset, len);
  }
  return ret;
}

size_t fs_write(int fd, const void *buf, size_t len) {
  size_t ret  = -1;
  size_t writelen = lenchoose(len, file_table[fd].size - file_table[fd].current);
  assert(writelen + file_table[fd].current <= file_table[fd].size);
  size_t offset = file_table[fd].disk_offset + file_table[fd].current;
  if(file_table[fd].write == NULL) {
    ret = ramdisk_write(buf, offset, writelen);
    file_table[fd].current += writelen;
  }
  else {
    ret = file_table[fd].write(buf, offset, len);
  }
  return ret;
}

size_t fs_lseek(int fd, size_t offset, int whence) {
  switch(whence) {
  case SEEK_SET:
    file_table[fd].current = offset;
    break;
  case SEEK_CUR:
    file_table[fd].current += offset;
    break;
  case SEEK_END:
    file_table[fd].current = file_table[fd].size + offset;
    break;
  default:
    panic("Unknown whence %d", whence);
    break;
  }
  return file_table[fd].current;
}

int fs_close(int fd){
  file_table[fd].current = 0;
  return 0;
}
