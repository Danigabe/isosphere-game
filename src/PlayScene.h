#ifndef ISOSPHERE_PLAYSCENE_H
#define ISOSPHERE_PLAYSCENE_H

#include "cScene.h"
#include "cCamera.h"
#include "cBlock.h"
#include "cBall.h"
#include "cSelection.h"
#include "Globals.h"

const char* const FILENAME_EXT = ".lvl";

enum PlaySceneState {
  STATE_EDITING,
  STATE_ROLLING,
  STATE_LEVEL_COMPLETED
};

class PlayScene : public cScene {
public:
  PlayScene(cGame* parent);

  bool Init();
  void Finalize();
  bool LoadLevel(int lvl);

  void Draw(cData *Data);
  void Logic();
  bool Input(unsigned char* keys, int mouse_x, int mouse_y);

private:
  void ModifyNumBlocks(const cBlock& block, bool erasing);
  void DrawHUD(cData *Data);
  void DrawSelBlock();
  void DrawRemBlock();
  void DrawLvlCompleted();
  void LoadShader();

  BlockMatrix3D map;
  cBall ball;
  cCamera camera;
  cSelection selection;

  int map_width, map_height, map_depth;
  int ball_initial_pos_x, ball_initial_pos_y, ball_initial_pos_z; // pos in tile space
  int ball_initial_dir;
  int level;
  int state;

  int numCube, numLCube, numSlope, numLSlope, numDir;

  static int glprogram;
};

#endif