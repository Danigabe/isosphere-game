#include "Globals.h"
#include "cGame.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;

void AppRender() {
  Game.Render();
}

void AppKeyboard(unsigned char key, int x, int y) {
  Game.ReadKeyboard(key,x,y,true);
}

void AppKeyboardUp(unsigned char key, int x, int y) {
  Game.ReadKeyboard(key,x,y,false);
}

void AppSpecialKeys(int key, int x, int y) {
  Game.ReadKeyboard(key,x,y,true);
}

void AppSpecialKeysUp(int key, int x, int y) {
  Game.ReadKeyboard(key,x,y,false);
}

void AppMouse(int button, int state, int x, int y) {
  Game.ReadMouse(button,!state,x,y);
}

void AppMouseMotion(int x, int y) {
  Game.ReadMouse(GLUT_LEFT_BUTTON, 2, x, y);
}

void AppMouseMotionPas(int x, int y) {
  Game.MoveMouse(x, y);
}

void AppIdle() {
  if (!Game.Loop())
    exit(0);
}

void main(int argc, char** argv) {
  //GLUT initialization
  glutInit(&argc, argv);

  //RGBA with double buffer
  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

  //Create centered window
  int res_x = glutGet(GLUT_SCREEN_WIDTH);
  int res_y = glutGet(GLUT_SCREEN_HEIGHT);
  int pos_x = (res_x>>1) - ((int)SCREEN_WIDTH>>1);
  int pos_y = (res_y>>1) - ((int)SCREEN_HEIGHT>>1);

  glutInitWindowPosition(pos_x, pos_y);
  glutInitWindowSize((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
  glutCreateWindow("Isosphere");

  /*glutGameModeString("800x600:32");
  glutEnterGameMode();*/

  //Make the default cursor disappear
  //glutSetCursor(GLUT_CURSOR_NONE);

  //Register callback functions
  glutDisplayFunc(AppRender);			
  glutKeyboardFunc(AppKeyboard);		
  glutKeyboardUpFunc(AppKeyboardUp);	
  glutSpecialFunc(AppSpecialKeys);	
  glutSpecialUpFunc(AppSpecialKeysUp);
  glutMouseFunc(AppMouse);
  glutMotionFunc(AppMouseMotion);
  glutPassiveMotionFunc(AppMouseMotionPas);
  glutIdleFunc(AppIdle);

  //Game initializations
  Game.Init();

  //Application loop
  glutMainLoop();
}