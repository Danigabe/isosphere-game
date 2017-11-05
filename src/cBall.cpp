#include "cBall.h"

cBall::cBall() {
  inGoal = false;
}

cBall::~cBall() {
}

void cBall::Render() {
  glPushMatrix();
  glTranslatef(pos.x, pos.y, pos.z);
  //glDepthMask(false);
  glColor3f(1.0f, 0.5967f, 0.3254f);
  glutSolidSphere(0.5f, 20, 20);
  //glDepthMask(true);
  glPopMatrix();
}

void cBall::Start() {
  dir = initial_dir;
  vel = 0.04f; // 2 blocks per sec
  inGoal = false;
}

void cBall::Stop() {
  vel = 0;
}

void cBall::SetPos(float x, float y, float z) {
  pos = cVector(x, y, z);
}

void cBall::SetInitialDir(int dir_) {
  initial_dir = dir_;
}

bool cBall::PhysStep(const BlockMatrix3D& map) {
  cVector basePos = pos - cVector(0.0f, 0.5f, 0.0f);
  int base_posx = (int)(basePos.x + 0.5f),
      base_posy = (int)(basePos.y + 0.5f),
      base_posz = (int)(basePos.z + 0.5f);
  if (!CheckBounds(map, base_posx, base_posy, base_posz))
    return true; // ball out of map

  cVector moveDir(0.0f, 0.0f, 0.0f);
  if (dir == DIR_UP)         moveDir.z = -vel;
  else if (dir == DIR_DOWN)  moveDir.z =  vel;
  else if (dir == DIR_RIGHT) moveDir.x = -vel;
  else if (dir == DIR_LEFT)  moveDir.x =  vel;

  float friction = 0.0f;
  if (!map[base_posx][base_posy][base_posz].TouchingUp(basePos, base_posx, base_posy, base_posz))
    moveDir.y -= 0.02;
  moveDir.x /= 4.0f;
  moveDir.z /= 4.0f;

  cVector newPos = pos + moveDir;
  cVector newBase = newPos - cVector(0.0f, 0.5f, 0.0f);
  int newbase_posx = (int)(newBase.x + 0.5f),
      newbase_posy = (int)(newBase.y + 0.5f),
      newbase_posz = (int)(newBase.z + 0.5f);
  if (!CheckBounds(map, newbase_posx, newbase_posy, newbase_posz))
    return true;
  if (map[newbase_posx][newbase_posy][newbase_posz].TouchingUp(newBase, newbase_posx, newbase_posy, newbase_posz)) {
    friction = map[newbase_posx][newbase_posy][newbase_posz].GetFriction();
    if ((map[newbase_posx][newbase_posy][newbase_posz].IsType(BLOCK_QUAD) ||
        map[newbase_posx][newbase_posy][newbase_posz].IsType(BLOCK_STACK_QUAD_QUAD)) &&
        (map[base_posx][base_posy][base_posz].IsType(BLOCK_SLOPE) ||
        map[base_posx][base_posy][base_posz].IsType(BLOCK_STACK_QUAD_SLOPE))) {
          newPos.y = (float)newbase_posy + 0.5f;
    }
    else if (map[newbase_posx][newbase_posy][newbase_posz].IsType(BLOCK_HALF_QUAD) &&
             map[base_posx][base_posy][base_posz].IsType(BLOCK_HALF_QUAD)) {
          newPos.y = (float)newbase_posy;
    }
    // touching slope
    if (map[newbase_posx][newbase_posy][newbase_posz].IsType(BLOCK_SLOPE)) {
      newPos.x = pos.x + moveDir.x*0.5f;
      newPos.z = pos.z + moveDir.z*0.5f;
      if (dir == map[newbase_posx][newbase_posy][newbase_posz].GetDir()) {
        vel *= 0.996f;
        newPos.y = pos.y + abs(moveDir.x*0.52f) + abs(moveDir.z*0.52f);
        moveDir.y = newPos.y - pos.y;
        if (vel < 0.005) {
          dir = (dir+2)%4;
          vel += 0.00025;
          friction = 0.0f;
        }
      }
      else if ((dir+2)%4 == map[newbase_posx][newbase_posy][newbase_posz].GetDir()) {
        vel *= 1.025;
        newPos.y = pos.y - abs(moveDir.x*0.5f) - abs(moveDir.z*0.5f);
        moveDir.y = newPos.y - pos.y;
      }
      else if (fequals(newBase.x, (float)newbase_posx) && fequals(newBase.z, (float)newbase_posz))
        dir = (map[newbase_posx][newbase_posy][newbase_posz].GetDir()+2)%4;
    }
    // touching half slope or stacked slope
    else if (map[newbase_posx][newbase_posy][newbase_posz].IsType(BLOCK_HALF_SLOPE) ||
            (map[newbase_posx][newbase_posy][newbase_posz].IsType(BLOCK_STACK_QUAD_SLOPE))) {// && newBase.y > (float)newbase_posy)) {
      newPos.x = pos.x + moveDir.x;
      newPos.z = pos.z + moveDir.z;
      if (dir == map[newbase_posx][newbase_posy][newbase_posz].GetDir()) {
        vel *= 0.9975;
        newPos.y = pos.y + abs(moveDir.x*0.52f) + abs(moveDir.z*0.52f);
        moveDir.y = newPos.y - pos.y;
        if (vel < 0.005) {
          dir = (dir+2)%4;
          vel += 0.00025;
          friction = 0.0f;
        }
      }
      else if ((dir+2)%4 == map[newbase_posx][newbase_posy][newbase_posz].GetDir()) {
        vel *= 1.0125;
        newPos.y = pos.y - abs(moveDir.x*0.5f) - abs(moveDir.z*0.5f);
        moveDir.y = newPos.y - pos.y;
      }
      else if (fequals(newBase.x, (float)newbase_posx) && fequals(newBase.z, (float)newbase_posz))
        dir = (map[newbase_posx][newbase_posy][newbase_posz].GetDir()+2)%4;
    }
    else {
      newPos.y = pos.y;
      moveDir.y = 0.0f;
    }
  }

  cVector frontDir = moveDir; frontDir.y = 0;
  cVector front = newPos + cVector::normalize(frontDir)*0.5f;
  int front_posx = (int)(front.x + 0.5f),
      front_posy = (int)(front.y + 0.5f),
      front_posz = (int)(front.z + 0.5f);

  if (CheckBounds(map, front_posx, front_posy, front_posz)) {
    if (map[front_posx][front_posy][front_posz].TouchingSide(front, dir, front_posy)) {
      newPos.x = pos.x;
      newPos.z = pos.z;
      dir = (dir+2)%4;
    }
  }
  else {
    dir = (dir+2)%4;
  }

  pos = newPos;
  vel -= friction;

  CheckOverBlock(map);

  if (vel < 0.0001)
    return true;
  return false;
}

bool cBall::IsInGoal() const {
  return inGoal;
}

bool cBall::CheckBounds(const BlockMatrix3D& map, int x, int y, int z) const {
  if (x < 0 || (unsigned int)x >= map.size())
    return false;
  if (y < 0 || (unsigned int)y >= map[x].size())
    return false;
  if (z < 0 || (unsigned int)z >= map[x][y].size())
    return false;
  return true;
}

void cBall::CheckOverBlock(const BlockMatrix3D& map) {
  // base in tile space
  cVector base = pos + cVector(0.5f, 0.025f, 0.5f);
  float modx = fmod(base.x, 1.0f),
        modz = fmod(base.z, 1.0f);

  if (fequals(modx, 0.5f, 0.05) && // is aproximately in
      fequals(modz, 0.5f, 0.05))   // the center of the block
  {
    int basex = (int)base.x,
        basey = (int)base.y,
        basez = (int)base.z;
    if (map[basex][basey][basez].IsType(BLOCK_DIRECTIONAL)) {
      if (dir != (map[basex][basey][basez].GetDir()+2)%4)
        if (vel < 0.05f)
          vel += 0.01f;
      dir = map[basex][basey][basez].GetDir();
    }
    if (map[basex][basey][basez].IsType(BLOCK_STACK_QUAD_DIR)) {
      if (dir != (map[basex][basey][basez].GetDir()+2)%4)
        if (vel < 0.05f)
          vel += 0.01f;
      dir = map[basex][basey][basez].GetDir();
    }
    if (map[basex][basey][basez].IsType(BLOCK_GOAL))
      inGoal = true;
  }
}