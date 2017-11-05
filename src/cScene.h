#ifndef ISOSPHERE_CSCENE_H
#define ISOSPHERE_CSCENE_H

#include "cData.h"

const int SCENE_WIDTH  = 16;
const int SCENE_DEPTH  = 32;
const int SCENE_HEIGHT = 4;

class cGame;

class cScene {
public:
  cScene(cGame* parent) { game = parent; }
  virtual ~cScene() { }

  virtual bool Init() { return true; }
  virtual void Finalize() { }
  virtual void Draw(cData* Data) { }
  virtual void Logic() { }
  // returns true if the game finishes
  virtual bool Input(unsigned char* keys, int mouse_x, int mouse_y) { return false; }

protected:
  cGame* game;
};

#endif