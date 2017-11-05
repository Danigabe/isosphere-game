#include "MenuScene.h"
#include "cGame.h"
#include "PlayScene.h"

const int GLUT_ENTER = 13;
const int GLUT_ESC   = 27;

MenuScene::MenuScene(cGame* game) : cScene(game) {
  state = MENU_MAINMENU;
  optionSelected = 0;
}

void MenuScene::Draw(cData* Data) {
  if (state == MENU_MAINMENU)            DrawMain();
  else if (state == MENU_INSTRUCTIONS)   DrawInstructions();
  else if (state == MENU_CREDITS)        DrawCredits();
  else if (state == MENU_LEVELSELECTION) DrawLevelSelection();
}

void MenuScene::Logic() {

}

bool MenuScene::Input(unsigned char* keys, int mouse_x, int mouse_y) {
  if (state == MENU_MAINMENU) {
    if (keys[GLUT_KEY_UP]) {
      keys[GLUT_KEY_UP] = false;
      --optionSelected; if (optionSelected < 0) optionSelected = 3;
    }
    if (keys[GLUT_KEY_DOWN]) {
      keys[GLUT_KEY_DOWN] = false;
      optionSelected = (optionSelected+1) % 4;
    }
    
	if (keys[GLUT_ENTER]) {
      keys[GLUT_ENTER] = false;
      if (optionSelected == 0) {
        state = MENU_LEVELSELECTION;
        optionSelected = 1;
      }
      else if (optionSelected == 1)
        state = MENU_INSTRUCTIONS;
      else if (optionSelected == 2)
        state = MENU_CREDITS;
      else if (optionSelected == 3)
        return true;
    }
  }
  else if (state == MENU_CREDITS || state == MENU_INSTRUCTIONS) {
    if (keys[GLUT_ESC]) {
      keys[GLUT_ESC] = false;
      state = MENU_MAINMENU;
    }
	if (keys[GLUT_ENTER]) {
      keys[GLUT_ENTER] = false;
      state = MENU_MAINMENU;
    }
  }
  else if (state == MENU_LEVELSELECTION) {
    if (keys[GLUT_ESC]) {
      keys[GLUT_ESC] = false;
      state = MENU_MAINMENU;
      optionSelected = 0;
    }
    if (keys[GLUT_KEY_UP]) {
      keys[GLUT_KEY_UP] = false;
      --optionSelected;
      if (optionSelected < 1)
        optionSelected = 1;
    }
    if (keys[GLUT_KEY_DOWN]) {
      keys[GLUT_KEY_DOWN] = false;
      ++optionSelected;
      if (optionSelected > MAX_LEVEL)
        optionSelected = MAX_LEVEL;
    }
    if (keys[GLUT_KEY_LEFT]) {
      keys[GLUT_KEY_LEFT] = false;
      optionSelected -= 5;
      if (optionSelected < 1)
        optionSelected = 1;
    }
    if (keys[GLUT_KEY_RIGHT]) {
      keys[GLUT_KEY_RIGHT] = false;
      optionSelected += 5;
      if (optionSelected > MAX_LEVEL)
        optionSelected = MAX_LEVEL;
    }
	if (keys[GLUT_ENTER]) {
      PlayScene* playscene = new PlayScene(game);
      playscene->Init();
      if (!playscene->LoadLevel(optionSelected))
        return true;
      game->ChangeScene(playscene);
    }
  }
  return false;
}

bool MenuScene::Init() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  cGame::Sounds.Stop();
  return true;
}

void MenuScene::DrawMain() {
  glColor3f(0.5, 0.5, 0.5);
  if (optionSelected == 0)
    glColor3f(1.0, 1.0, 1.0);
  write("PLAY", 368, 318, 2);

  glColor3f(0.5, 0.5, 0.5);
  if (optionSelected == 1)
    glColor3f(1.0, 1.0, 1.0);
  write("INSTRUCTIONS", 304, 300, 2);

  glColor3f(0.5, 0.5, 0.5);
  if (optionSelected == 2)
    glColor3f(1.0, 1.0, 1.0);
  write("CREDITS", 344, 282, 2);

  glColor3f(0.5, 0.5, 0.5);
  if (optionSelected == 3)
    glColor3f(1.0, 1.0, 1.0);
  write("EXIT", 368, 264, 2);
  
  glColor3f(1.0, 1.0, 1.0);
}

void MenuScene::DrawCredits() {
  write("Game programmed by", 256, 300, 2);
  write("Daniel Galacho", 288, 282, 2);
}

void MenuScene::DrawInstructions() {
  write("wasd: move camera  ", 248, 356, 2);
  write("e:    start        ", 248, 340, 2);
  write("r:    reset level  ", 248, 324, 2);

  write("1:    cube         ", 248, 308, 2);
  write("2:    little cube  ", 248, 292, 2);
  write("3:    slope        ", 248, 276, 2);
  write("4:    little slope ", 248, 260, 2);
  write("5:    direction    ", 248, 244, 2);
  write("6:    erase block  ", 248, 228, 2);

}

void MenuScene::DrawLevelSelection() {
  glColor3f(0.5f, 0.5f, 0.5f);
  write("select level:", 296, 492, 2);

  if (optionSelected == 1)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("01", 292, 400, 2);

  if (optionSelected == 2)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("02", 292, 350, 2);

  if (optionSelected == 3)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("03", 292, 300, 2);

  if (optionSelected == 4)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("04", 292, 250, 2);

  if (optionSelected == 5)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("05", 292, 200, 2);

  if (optionSelected == 6)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("06", 492, 400, 2);

  if (optionSelected == 7)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("07", 492, 350, 2);

  if (optionSelected == 8)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("08", 492, 300, 2);

  if (optionSelected == 9)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("09", 492, 250, 2);

  if (optionSelected == 10)
    glColor3f(1.0f, 1.0f, 1.0f);
  else
    glColor3f(0.5f, 0.5f, 0.5f);
  write("10", 492, 200, 2);
}