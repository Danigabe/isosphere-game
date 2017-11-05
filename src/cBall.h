#ifndef ISOSPHERE_CBALL_H
#define ISOSPHERE_CBALL_H

#include "Globals.h"
#include "cVector.h"
#include "cBlock.h"

class cBall {
public:
  cBall();
  ~cBall();

  void Render();
  void Start();
  void Stop();
  void SetPos(float x, float y, float z);
  void SetInitialDir(int dir);
  // devuelve true si la bola se ha parado o ha llegado a la meta
  bool PhysStep(const BlockMatrix3D& map);

  bool IsInGoal() const;

private:
  bool CheckBounds(const BlockMatrix3D& map, int x, int y, int z) const;
  void CheckOverBlock(const BlockMatrix3D& map);

  cVector pos;
  int dir;
  float vel;
  int initial_dir;
  bool inGoal;
};

#endif