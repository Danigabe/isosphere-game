#include "cSelection.h"

cSelection::cSelection(BlockMatrix3D* map_) {
  selBlock.SetColor(1.0f, 0.2745f, 0.2745f, 0.75f);
  map = map_;
  erase = false;
}

void cSelection::UpdateSelection(float screenX, float screenY, const cCamera& camera) {
  if (CheckLimits())
    (*map)[tilex][tiley][tilez].SetAlpha(1.0f);

  // openGL expects y = 0 at the bottom-left corner
  screenY = SCREEN_HEIGHT - screenY;

  float zVal;
  glReadPixels(screenX,screenY,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&zVal);

  cVector position = camera.GetPosition();
  cVector view = cVector::normalize(camera.GetViewDir());
  cVector up   = camera.GetUpVector();

  cVector screenHorizontally = cVector::normalize(cVector::cross(view, up));
  cVector screenVertically   = cVector::normalize(cVector::cross(screenHorizontally, view));
  
  static const float radFOVy = FOVY * DEGTORAD;
  float halfHeight = tan(radFOVy/2.0f) * ZNEAR;
  float halfScaledARatio = halfHeight * WRATIO;

  screenVertically   *= halfHeight;
  screenHorizontally *= halfScaledARatio;

  // normalize to 1
  screenX -= SCREEN_WIDTH/2.0f;
  screenX /= SCREEN_WIDTH/2.0f;
  screenY -= SCREEN_HEIGHT/2.0f;
  screenY /= SCREEN_HEIGHT/2.0f;

  cVector mousePosInWorld = position + view*ZNEAR +
                            screenHorizontally*screenX +
                            screenVertically*screenY;
  cVector rayDirection    = cVector::normalize(mousePosInWorld - position);

  float zn = 2.0 * zVal - 1.0;
  float dist = 2.0 * ZNEAR*ZFAR / (ZFAR + ZNEAR - zn*(ZFAR - ZNEAR));

  if (erase) {
    cVector selection = mousePosInWorld + rayDirection*(dist+0.05) + cVector(0.5f, 0.5f, 0.5f);
    
    tilex = selection.x;
    tiley = selection.y;
    tilez = selection.z;

    if (CheckLimits()) {
      if (tiley < maxY-1 && (*map)[tilex][tiley+1][tilez].IsType(BLOCK_DIRECTIONAL))
        ++tiley;
      if ((*map)[tilex][tiley][tilez].GetErasable())
        (*map)[tilex][tiley][tilez].SetAlpha(0.75f);
    }

    return;
  }

  // + vec(0.5, 0.5, 0.5) because is the ponting tile
  cVector pointing  = mousePosInWorld + rayDirection*dist + cVector(0.5f, 0.5f, 0.5f);
  cVector selection = mousePosInWorld + rayDirection*(dist-0.2f) + cVector(0.5f, 0.5f, 0.5f);

  int pointingx = pointing.x;
  int pointingy = pointing.y;
  int pointingz = pointing.z;

  tilex = selection.x;
  tiley = selection.y;
  tilez = selection.z;

  if (CheckLimits() && tiley > 0 &&
      ((*map)[tilex][tiley-1][tilez].IsType(BLOCK_SLOPE) ||
       (*map)[tilex][tiley-1][tilez].IsType(BLOCK_HALF_SLOPE) ||
       (*map)[tilex][tiley-1][tilez].IsType(BLOCK_STACK_QUAD_SLOPE))) {
         // block over a slope
         tilex = tiley = tilez = -1;
  }

  if (CheckLimits() && tiley > 0 &&
      (*map)[tilex][tiley-1][tilez].IsNull())
    // block over a nullblock
    tilex = tiley = tilez = -1;

  if (CheckLimits() && tiley > 0 &&
      (*map)[tilex][tiley-1][tilez].IsType(BLOCK_INVISIBLE))
    // block over a invisible block
    tilex = tiley = tilez = -1;

  if (tiley == 0)
    tilex = tiley = tilez = -1;
}

cBlock cSelection::Pick() {
  if (CheckLimits()) {
    if (erase)
      return EraseBlock();
    if ((*map)[tilex][tiley][tilez].IsNull()) {
      if (tiley > 0 && (*map)[tilex][tiley-1][tilez].IsNull())
        return cBlock();
      (*map)[tilex][tiley][tilez] = selBlock;
      (*map)[tilex][tiley][tilez].SetColor(1.0f, 0.2745f, 0.2745f);
      (*map)[tilex][tiley][tilez].SetErasable(true);
      return selBlock;
    }
    else {
      cBlock stack = (*map)[tilex][tiley][tilez].Stackable(selBlock);
      if (!stack.IsNull()) {
        (*map)[tilex][tiley][tilez] = stack;
        (*map)[tilex][tiley][tilez].SetColor(1.0f, 0.2745f, 0.2745f);
        return selBlock;
      }
    }
  }
  return cBlock();
}

void cSelection::SetLimits(int x, int y, int z) {
  maxX = x;
  maxY = y;
  maxZ = z;
}

cBlock& cSelection::GetSelectedBlock() {
  return selBlock;
}

void cSelection::SetSelectionBlock(const cBlock& block) {
  selBlock = block;
  SetErase(false);
}

void cSelection::Render() {
  if (erase)
    return;
  if (CheckLimits()) {
    if ((*map)[tilex][tiley][tilez].IsNull()) {
      glDepthMask(false);
      selBlock.Render(tilex, tiley, tilez);
      glDepthMask(true);
    }
    else {
      cBlock stack = (*map)[tilex][tiley][tilez].Stackable(selBlock);
      if (!stack.IsNull()) {
        glDepthMask(false);
        stack.SetColor(selBlock);
        stack.Render(tilex, tiley, tilez);
        glDepthMask(true);
      }
    }
  }
}

bool cSelection::CheckLimits() {
  if (tilex < 0 || tilex >= maxX)
    return false;
  if (tiley < 0 || tiley >= maxY)
    return false;
  if (tilez < 0 || tilez >= maxZ)
    return false;
  return true;
}

cBlock cSelection::EraseBlock() {
  cBlock retBlock;
  if (tiley < maxY-1 && !(*map)[tilex][tiley+1][tilez].IsNull())
    return retBlock;
  if ((*map)[tilex][tiley][tilez].GetErasable()) {
    retBlock = (*map)[tilex][tiley][tilez];
    if ((*map)[tilex][tiley][tilez].IsType(BLOCK_STACK_QUAD_QUAD) ||
        (*map)[tilex][tiley][tilez].IsType(BLOCK_STACK_QUAD_SLOPE) ||
        (*map)[tilex][tiley][tilez].IsType(BLOCK_STACK_QUAD_DIR))
      (*map)[tilex][tiley][tilez] = cBlock(BLOCK_HALF_QUAD, DIR_UP);
    else
      (*map)[tilex][tiley][tilez] = cBlock();
    (*map)[tilex][tiley][tilez].SetAlpha(1.0f);
  }
  if (retBlock.IsType(BLOCK_STACK_QUAD_QUAD))
    retBlock = cBlock(BLOCK_HALF_QUAD, DIR_UP);
  if (retBlock.IsType(BLOCK_STACK_QUAD_SLOPE))
    retBlock = cBlock(BLOCK_HALF_SLOPE, DIR_UP);
  if (retBlock.IsType(BLOCK_STACK_QUAD_DIR))
    retBlock = cBlock(BLOCK_DIRECTIONAL, DIR_UP);
  return retBlock;
}

void cSelection::SetErase(bool er) {
  erase = er;
}

bool cSelection::GetErase() const {
  return erase;
}