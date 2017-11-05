#include "cSound.h"

cSound::cSound() {
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);

  FMOD_System_CreateSound(system, "res/wind.mp3", FMOD_HARDWARE|FMOD_LOOP_NORMAL, 0, &sounds[MUSIC_ONLEVEL]);
}

cSound::~cSound() {
}

void cSound::Play(int soundID) {
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sounds[soundID], 0, &channel);
  FMOD_System_Update(system);
}

void cSound::Stop() {
  FMOD_Channel_Stop(channel);
  FMOD_System_Update(system);
}