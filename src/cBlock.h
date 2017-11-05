#ifndef ISOSPHERE_CBLOCK_H
#define ISOSPHERE_CBLOCK_H

#include "Globals.h"
#include "cVector.h"

enum BlockType {
  BLOCK_GROUND,
  BLOCK_GOAL,

  BLOCK_QUAD,
  BLOCK_SLOPE,
  BLOCK_HALF_QUAD,
  BLOCK_HALF_SLOPE,
  BLOCK_DIRECTIONAL,
  BLOCK_STACK_QUAD_QUAD,
  BLOCK_STACK_QUAD_SLOPE,
  BLOCK_STACK_QUAD_DIR,

  // prevents putting blocks in certain positions
  BLOCK_INVISIBLE,


  NUM_BLOCKS,
  // invalid block
  NULLBLOCK = -1
};

enum Direction {
  DIR_UP,
  DIR_LEFT,
  DIR_DOWN,
  DIR_RIGHT
};

class cBlock {
public:
  static void Init();
  static void Finalize();

  cBlock() : type(NULLBLOCK), direction(DIR_UP), erasable(false) { }
  cBlock(int type, int direction, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
  ~cBlock() { }

  void Render(float x, float y, float z) const;
  void RawRender() const;

  void SetColor(float r, float g, float b, float a = 1.0f);
  void SetColor(const cBlock& sourceBlock);
  void SetAlpha(float a);
  void SetErasable(bool er);
  bool GetErasable() const;

  cBlock& operator=(const cBlock& b); // not modifies color
  bool IsNull() const;
  bool IsType(int type_) const;
  void NextDir();
  int  GetDir() const;

  // devuelve la direccion de movimiento del tile
  cVector GetMoveDir(const cVector& prevDir) const;
  bool TouchingUp(const cVector& point, int x, int y, int z) const;
  bool TouchingSide(const cVector& point, int pdir, int tiley) const;
  float GetFriction() const;

  // si es apilable devuelve los bloques apilados,
  // sino devuelve un bloque nulo
  cBlock Stackable(const cBlock& upperBlock) const;

private:
  void Rotate() const;
  static GLuint block_DL;
  int type, direction;
  float red, green, blue, alpha;
  bool erasable;
};

typedef std::vector<cBlock> BlockVector;
typedef std::vector<BlockVector> BlockMatrix;
typedef std::vector<BlockMatrix> BlockMatrix3D;

#endif