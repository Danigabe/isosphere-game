#ifndef ISOSPHERE_CSELECTION_H
#define ISOSPHERE_CSELECTION_H

#include "cVector.h"
#include "cCamera.h"
#include "cBlock.h"

class cSelection {
public:
  cSelection(BlockMatrix3D* map);

  void UpdateSelection(float screenX, float screenY, const cCamera& camera);
  cBlock Pick();
  void Render();
  void SetErase(bool er);
  bool GetErase() const;
  
  void SetLimits(int x, int y, int z);
  cBlock& GetSelectedBlock();
  void SetSelectionBlock(const cBlock& block);

private:
  bool CheckLimits();
  cBlock EraseBlock();

  cBlock selBlock;
  int maxX, maxY, maxZ;
  int tilex, tiley, tilez;
  BlockMatrix3D* map;
  bool erase;
};

#endif