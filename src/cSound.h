#ifndef ISOSPHERE_CSOUND_H
#define ISOSPHERE_CSOUND_H

#include <fmod.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

enum Sounds {
  // Sound identifiers
  MUSIC_ONLEVEL,

  // Sound array size
  NUM_SOUNDS
};

class cSound {
public:
  cSound();
  ~cSound();
  void Play(int soundID);
  void Stop();

private:
  FMOD_SYSTEM *system;
  FMOD_CHANNEL *channel;
  FMOD_SOUND *sounds[NUM_SOUNDS];
};

#endif