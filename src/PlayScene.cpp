#include "PlayScene.h"
#include "cGame.h"
#include "MenuScene.h"
#include "Shaders.h"
#include <fstream>
using namespace std;

int PlayScene::glprogram = 0;

PlayScene::PlayScene(cGame* parent) : cScene(parent), selection(&map) {
  state = STATE_EDITING;
  level = 0;
}

bool PlayScene::Init() {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  LoadShader();
  cBlock::Init();
  return true;
}

void PlayScene::Finalize() {
  cBlock::Finalize();
}

bool PlayScene::LoadLevel(int lvl) {
  if (lvl > MAX_LEVEL) {
    MenuScene* ms = new MenuScene(game);
    ms->Init();
    game->ChangeScene(ms);
    return false;
  }
  if (lvl != level) {
    if (lvl == 1) {
      cGame::Sounds.Stop();
      cGame::Sounds.Play(MUSIC_ONLEVEL);
    }
    level = lvl;
  }

  char filename[16];
  if (level < 10) sprintf_s(filename, "res/0%d%s", level, FILENAME_EXT);
  else            sprintf_s(filename, "res/%d%s",  level, FILENAME_EXT);

  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return false;
  }

  file >> map_width >> map_height >> map_depth;
  file >> ball_initial_pos_x >> ball_initial_pos_y >> ball_initial_pos_z;
  file >> ball_initial_dir;

  map = BlockMatrix3D(map_width, BlockMatrix(map_height, BlockVector(map_depth)));
  ball.SetPos(ball_initial_pos_x, ball_initial_pos_y, ball_initial_pos_z);
  ball.SetInitialDir(ball_initial_dir);
  selection.SetLimits(map_width, map_height, map_depth);

  float cameraDist;
  file >> cameraDist;
  camera.SetDistance(cameraDist);
  camera.SetLookPoint((map_width-1)/2.0f, (map_height-1)/2.0f, (map_depth-1)/2.0f);
  camera.MoveCamera(PI, PI/4.0f);

  file >> numCube >> numLCube >> numSlope >> numLSlope >> numDir;

  int blockx, blocky, blockz;
  while (file >> blockx >> blocky >> blockz) {
    int type, dir;
    file >> type >> dir;
    map[blockx][blocky][blockz] = cBlock(type, dir);
    map[blockx][blocky][blockz].SetColor(0.0f, 0.6352f, 0.9098f);
    map[blockx][blocky][blockz].SetErasable(false);
    if (type == BLOCK_GOAL)
      map[blockx][blocky][blockz].SetColor(0.4156f, 0.6588f, 0.3098f);
  }

  map[ball_initial_pos_x][ball_initial_pos_y][ball_initial_pos_z] = cBlock(BLOCK_INVISIBLE, DIR_UP);
  map[ball_initial_pos_x][ball_initial_pos_y][ball_initial_pos_z].SetErasable(false);

  state = STATE_EDITING;
  return true;
}

void PlayScene::Draw(cData *Data) {
  camera.UpdateCamera();
  
  for (int i = 0; i < map_width; ++i)
    for (int j = 0; j < map_height; ++j)
      for (int k = 0; k < map_depth; ++k)
        map[i][j][k].Render(i, j, k);

  glUseProgram(glprogram);
  ball.Render();
  glUseProgram(0);
  selection.Render();

  DrawHUD(Data);

  if (state == STATE_LEVEL_COMPLETED)
    DrawLvlCompleted();
}

void PlayScene::Logic() {
  if (state == STATE_ROLLING) {
    if (ball.PhysStep(map)) {
      state = STATE_EDITING;
      ball.Stop();
      ball.SetPos(ball_initial_pos_x, ball_initial_pos_y, ball_initial_pos_z);
    }
    if (ball.IsInGoal())
      state = STATE_LEVEL_COMPLETED;
  }
  else if (state == STATE_LEVEL_COMPLETED) {
    static int tick = 0;
    if (tick == 200) {
      LoadLevel(level+1);
      tick = 0;
    }
    ++tick;
  }
}

bool PlayScene::Input(unsigned char* keys, int mouse_x, int mouse_y) {
  if (state == STATE_LEVEL_COMPLETED)
    return false;

  if (keys[27]) {
    keys[27] = false;
    MenuScene* ms = new MenuScene(game);
    ms->Init();
    game->ChangeScene(ms);
    return false;
  }

  static int prevMX = mouse_x;
  static int prevMY = mouse_y;
  int despMX = mouse_x - prevMX;
  int despMY = prevMY - mouse_y;
  prevMX = mouse_x;
  prevMY = mouse_y;

  if (keys['r']) {
    cCamera prevCam = camera;
    bool loaded = LoadLevel(level);
    camera = prevCam;
    return !loaded;
  }

  // movimiento de camara
  if (keys['w'])
    camera.MoveCamera(0.0f, 0.1f);
  if (keys['s'])
    camera.MoveCamera(0.0f, -0.1f);
  if (keys['d'])
    camera.MoveCamera(0.1f, 0.0f);
  if (keys['a'])
    camera.MoveCamera(-0.1f, 0.0f);

  if (keys[256] == 2) { // mouse moving while clic
    float despX = despMX/2.0f * DEGTORAD;
    float despY = despMY/2.0f * DEGTORAD;
    camera.MoveCamera(despX, despY);
  } // fin movimiento de camara

  if (state == STATE_EDITING) {
    if (keys['1'] && numCube != 0) {
      if (selection.GetSelectedBlock().IsType(BLOCK_QUAD))
        selection.GetSelectedBlock().NextDir();
      else
        selection.SetSelectionBlock(cBlock(BLOCK_QUAD, DIR_UP));
      keys['1'] = false;
    }
    if (keys['2'] && numLCube != 0) {
      if (selection.GetSelectedBlock().IsType(BLOCK_HALF_QUAD))
        selection.GetSelectedBlock().NextDir();
      else
        selection.SetSelectionBlock(cBlock(BLOCK_HALF_QUAD, DIR_UP));
      keys['2'] = false;
    }
    if (keys['3'] && numSlope != 0) {
      if (selection.GetSelectedBlock().IsType(BLOCK_SLOPE))
        selection.GetSelectedBlock().NextDir();
      else
        selection.SetSelectionBlock(cBlock(BLOCK_SLOPE, DIR_UP));
      keys['3'] = false;
    }
    if (keys['4'] && numLSlope != 0) {
      if (selection.GetSelectedBlock().IsType(BLOCK_HALF_SLOPE))
        selection.GetSelectedBlock().NextDir();
      else
        selection.SetSelectionBlock(cBlock(BLOCK_HALF_SLOPE, DIR_UP));
      keys['4'] = false;
    }
    if (keys['5'] && numDir != 0) {
      if (selection.GetSelectedBlock().IsType(BLOCK_DIRECTIONAL))
        selection.GetSelectedBlock().NextDir();
      else
        selection.SetSelectionBlock(cBlock(BLOCK_DIRECTIONAL, DIR_UP));
      keys['5'] = false;
    }
    if (keys['6']) {
      selection.SetSelectionBlock(cBlock());
      selection.SetErase(!selection.GetErase());
      keys['6'] = false;
    }
    if (keys['0']) {
      selection.SetSelectionBlock(cBlock());
      keys['0'] = false;
    }
    if (despMX || despMY || camera.GetMoved())
      selection.UpdateSelection(mouse_x, mouse_y, camera);
    if (keys[256] == 1) {
      keys[256] = false;
      cBlock usedBlock = selection.Pick();
      if (selection.GetErase())
        ModifyNumBlocks(usedBlock, true);
      else
        ModifyNumBlocks(usedBlock, false);
    }

    if (keys['e']) {
      keys['e'] = false;
      state = STATE_ROLLING;
      selection.SetSelectionBlock(cBlock());
      ball.Start();
    }
  }
  else if (state == STATE_ROLLING) {
    if (keys['e']) {
      keys['e'] = false;
      state = STATE_EDITING;
      ball.Stop();
      ball.SetPos(ball_initial_pos_x, ball_initial_pos_y, ball_initial_pos_z);
    }
  }
  return false;
}

void PlayScene::ModifyNumBlocks(const cBlock& block, bool erasing) {
  int* modVar = NULL;
  if (block.IsType(BLOCK_QUAD))
    modVar = &numCube;
  if (block.IsType(BLOCK_HALF_QUAD))
    modVar = &numLCube;
  if (block.IsType(BLOCK_SLOPE))
    modVar = &numSlope;
  if (block.IsType(BLOCK_HALF_SLOPE))
    modVar = &numLSlope;
  if (block.IsType(BLOCK_DIRECTIONAL))
    modVar = &numDir;

  if (modVar != NULL) {
    if (erasing)
      ++(*modVar);
    else
      --(*modVar);

    if ((*modVar) == 0)
      selection.SetSelectionBlock(cBlock());
  }
}

void PlayScene::DrawHUD(cData *Data) {
  glDisable(GL_DEPTH_TEST);

  DrawSelBlock();
  DrawRemBlock();

  glEnable(GL_DEPTH_TEST);
}

void PlayScene::DrawSelBlock() {
  glColor3f(1.0f, 1.0f, 1.0f);
  drawRect(25, 547, 144, 28);
  glColor3f(0.0f, 0.0f, 0.0f);
  drawRect(27, 549, 140, 24);

  glColor3f(0.8f, 0.8f, 0.8f);
  write("selected block:", 30, 562);

  glColor3f(1.0f, 1.0f, 1.0f);
  if (selection.GetErase())
    write("erasing blocks", 30, 552);
  else if (selection.GetSelectedBlock().IsType(BLOCK_QUAD))
    write(QUAD_NAME, 30, 552);
  else if (selection.GetSelectedBlock().IsType(BLOCK_HALF_QUAD))
    write(HALF_QUAD_NAME, 30, 552);
  else if (selection.GetSelectedBlock().IsType(BLOCK_SLOPE))
    write(SLOPE_NAME, 30, 552);
  else if (selection.GetSelectedBlock().IsType(BLOCK_HALF_SLOPE))
    write(HALF_SLOPE_NAME, 30, 552);
  else if (selection.GetSelectedBlock().IsType(BLOCK_DIRECTIONAL))
    write(DIR_NAME, 30, 552);
  else
    write("none", 30, 552);
}

void PlayScene::DrawRemBlock() {
  glColor3f(1.0, 1.0, 1.0);
  drawRect(25, 465, 144, 68);
  glColor3f(0.0f, 0.0f, 0.0f);
  drawRect(27, 467, 140, 64);

  glColor3f(0.8f, 0.8f, 0.8f);
  write("remaining blocks:", 30, 520);

  glColor3f(1.0f, 1.0f, 1.0f);
  write(QUAD_NAME, 30, 510);
  write(HALF_QUAD_NAME, 30, 500);
  write(SLOPE_NAME, 30, 490);
  write(HALF_SLOPE_NAME, 30, 480);
  write(DIR_NAME, 30, 470);

  write(intToString(numCube),   158, 510);
  write(intToString(numLCube),  158, 500);
  write(intToString(numSlope),  158, 490);
  write(intToString(numLSlope), 158, 480);
  write(intToString(numDir),    158, 470);
}

void PlayScene::DrawLvlCompleted() {
  glDisable(GL_DEPTH_TEST);
  glColor3f(1.0f, 1.0f, 1.0f);
  drawRect(308, 272, 184, 56);
  glColor3f(0.0f, 0.0f, 0.0f);
  drawRect(312, 276, 176, 48);

  glColor3f(1.0f, 1.0f, 1.0f);
  write("level", 360, 302, 2);
  write("completed", 328, 282, 2);
  glEnable(GL_DEPTH_TEST);
}

void PlayScene::LoadShader() {
  static bool loaded = false;
  if (loaded)
    return;

  glewInit();
  glprogram = LoadShaders(inkSh_vert, inkSh_frag);
  loaded = true;
}