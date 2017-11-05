#include "cGame.h"
#include "Globals.h"
#include "MenuScene.h"

cData  cGame::Data;
cSound cGame::Sounds;

cGame::cGame() {
}

cGame::~cGame() {
}

bool cGame::Init() {
  bool res = true;

  //Graphics initialization
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOVY, WRATIO, ZNEAR, ZFAR);
  glMatrixMode(GL_MODELVIEW);
	
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.05f);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // for drawing outlines correctly
  glEnable(GL_POLYGON_OFFSET_LINE);
  glPolygonOffset(-1.0f, -1.0f);
  glEnable(GL_LINE_SMOOTH);

  //Scene initialization
  if (!Data.LoadImageNearest(IMG_FONT, "res/font.png", GL_RGBA))
    return false;

  MenuScene* ms = new MenuScene(this);
  ms->Init();
  Scene = ms;

  return res;
}

bool cGame::Loop() {
  bool res = true;

  int t1, t2;
  t1 = glutGet(GLUT_ELAPSED_TIME);

  res = Process();
  if (res)
    Render();

  do {
      t2 = glutGet(GLUT_ELAPSED_TIME);
  } while (t2-t1 < 20);

  return res;
}

void cGame::Finalize() {
  Scene->Finalize();
  delete Scene;
}

void cGame::ChangeScene(cScene* scene) {
  Scene->Finalize();
  delete Scene;
  Scene = scene;
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press) {
  keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON)
    keys[256] = state;
  mouse_x = x;
  mouse_y = y;
}

void cGame::MoveMouse(int x, int y) {
  mouse_x = x;
  mouse_y = y;
}

//Process
bool cGame::Process() {
  bool res = true;
	
  //Process Input
  if (Scene->Input(keys, mouse_x, mouse_y))
    res = false;
  if (keys[27])
    res = false;	
	
  //Game Logic
  Scene->Logic();

  return res;
}

//Output
void cGame::Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Scene->Draw(&Data);
  glutSwapBuffers();
}