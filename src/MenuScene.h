#ifndef ISOSPHERE_MENUSCENE_H
#define ISOSPHERE_MENUSCENE_H

#include "cScene.h"

enum MenuState {
  MENU_MAINMENU,
  MENU_CREDITS,
  MENU_INSTRUCTIONS,
  MENU_LEVELSELECTION
};

class MenuScene : public cScene {
public:
  MenuScene(cGame* game);
  void Draw(cData* Data);
  void Logic();
  bool Input(unsigned char* keys, int mouse_x, int mouse_y);

  bool Init();

private:
  void DrawMain();
  void DrawCredits();
  void DrawInstructions();
  void DrawLevelSelection();

  int state;
  int optionSelected;
};

#endif