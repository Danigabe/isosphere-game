#ifndef ISOSPHERE_CGAME_H
#define ISOSPHERE_CGAME_H

#include "cScene.h"
#include "cData.h"
#include "cSound.h"

class cGame {
public:
  static cData  Data;
  static cSound Sounds;

  cGame();
  virtual ~cGame();

  bool Init();
  bool Loop();
  void Finalize();

  void ChangeScene(cScene* scene);

  //Input
  void ReadKeyboard(unsigned char key, int x, int y, bool press);
  void ReadMouse(int button, int state, int x, int y);
  void MoveMouse(int x, int y);
  //Process
  bool Process();
  //Output
  void Render();

private:
  unsigned char keys[257]; // 256 = left clic
  int mouse_x, mouse_y;
  cScene *Scene;
};

#endif