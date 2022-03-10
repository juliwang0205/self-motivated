#include <NDL.h>
#include <SDL.h>

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
  //panic("SDL_OpenAudio hasn't been implemented\n");
  return 0;
}

void SDL_CloseAudio() {
  //panic("SDL_CloseAudio hasn't been implemented\n");
}

void SDL_PauseAudio(int pause_on) {
  //panic("SDL_PauseAudio hasn't been implemented\n");
}

void SDL_MixAudio(uint8_t *dst, uint8_t *src, uint32_t len, int volume) {
  //panic("SDL_MixAudio hasn't been implemented\n");
}

SDL_AudioSpec *SDL_LoadWAV(const char *file, SDL_AudioSpec *spec, uint8_t **audio_buf, uint32_t *audio_len) {
  //panic("SDL_LoadWAV hasn't been implemented\n");
  return NULL;
}

void SDL_FreeWAV(uint8_t *audio_buf) {
  //panic("SDL_FreeWAV hasn't been implemented\n");
}

void SDL_LockAudio() {
  //panic("SDL_LockAudio hasn't been implemented\n");
}

void SDL_UnlockAudio() {
  //panic("SDL_UnlockAudio hasn't been implemented\n");
}
