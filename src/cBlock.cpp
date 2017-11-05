#include "cBlock.h"

GLuint cBlock::block_DL;

void cBlock::Init() {
  block_DL = glGenLists(NUM_BLOCKS);

  glNewList(block_DL+BLOCK_GROUND, GL_COMPILE);
  glBegin(GL_QUADS);
    // top
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    // front
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-100.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-100.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    // back
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-100.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-100.5f,-0.5f);
    // right
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-100.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-100.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, 0.5f, 0.5f);
    // left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-100.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,-100.5f,-0.5f);
  glEnd();
  glEndList();

  glNewList(block_DL+BLOCK_QUAD, GL_COMPILE);
  glBegin(GL_QUADS);
    // top
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    // bot
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // front
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    // back
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // right
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, 0.5f, 0.5f);
    // left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
  glEnd();
  glEndList();

  glNewList(block_DL+BLOCK_SLOPE, GL_COMPILE);
  glBegin(GL_QUADS);
    // bot
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // back
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // slope
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
  glEnd();
  glBegin(GL_TRIANGLES);
    // right
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.5f,-0.5f);
    // left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
  glEnd();
  glEndList();

  glNewList(block_DL+BLOCK_HALF_QUAD, GL_COMPILE);
  glBegin(GL_QUADS);
    // top
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, 0.0f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.0f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
    // bot
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // front
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.0f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
    // back
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // right
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.0f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, 0.0f, 0.5f);
    // left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
  glEnd();
  glEndList();

  glNewList(block_DL+BLOCK_HALF_SLOPE, GL_COMPILE);
  glBegin(GL_QUADS);
    // bot
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // back
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    // slope
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.0f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
  glEnd();
  glBegin(GL_TRIANGLES);
    // right
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,-0.5f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f, 0.0f,-0.5f);
    // left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f,-0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,-0.5f,-0.5f);
  glEnd();
  glEndList();

  glNewList(block_DL+BLOCK_STACK_QUAD_QUAD, GL_COMPILE);
    glCallList(block_DL+BLOCK_HALF_QUAD);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glCallList(block_DL+BLOCK_HALF_QUAD);
    glPopMatrix();
  glEndList();

  glNewList(block_DL+BLOCK_STACK_QUAD_SLOPE, GL_COMPILE);
    glCallList(block_DL+BLOCK_HALF_QUAD);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glCallList(block_DL+BLOCK_HALF_SLOPE);
    glPopMatrix();
  glEndList();

  glNewList(block_DL+BLOCK_DIRECTIONAL, GL_COMPILE);
    glBegin(GL_POLYGON);
      glVertex3f( 0.0f, -0.45f, -0.3f);
      glVertex3f(-0.2f, -0.45f,  0.0f);
      glVertex3f(-0.1f, -0.45f,  0.0f);
      glVertex3f(-0.1f, -0.45f,  0.3f);
      glVertex3f( 0.1f, -0.45f,  0.3f);
      glVertex3f( 0.1f, -0.45f,  0.0f);
      glVertex3f( 0.2f, -0.45f,  0.0f);
    glEnd();
  glEndList();

  glNewList(block_DL+BLOCK_STACK_QUAD_DIR, GL_COMPILE);
    glCallList(block_DL+BLOCK_HALF_QUAD);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glCallList(block_DL+BLOCK_DIRECTIONAL);
    glPopMatrix();
  glEndList();

  glNewList(block_DL+BLOCK_GOAL, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.49f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.49f,-0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.49f,-0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.49f, 0.5f);
  glEnd();
  glEndList();
}

void cBlock::Finalize() {
  glDeleteLists(block_DL, NUM_BLOCKS);
}

cBlock::cBlock(int type_, int direction_, float r, float g, float b, float a) {
  type = type_;
  direction = direction_;
  SetColor(r, g, b, a);
  erasable = false;
}

void cBlock::Rotate() const {
  switch (direction) {
    case DIR_UP:                                 break;
    case DIR_DOWN:  glRotatef(180, 0.0,1.0,0.0); break;
    case DIR_RIGHT: glRotatef( 90, 0.0,1.0,0.0); break;
    case DIR_LEFT:  glRotatef(-90, 0.0,1.0,0.0); break;
  }
}

void cBlock::Render(float x, float y, float z) const {
  if (type == NULLBLOCK)
    return;

  glPushMatrix();
  glTranslatef(x,y,z);
  Rotate();
  RawRender();

  glPopMatrix();
}

void cBlock::RawRender() const {
  if (type == BLOCK_DIRECTIONAL || type == BLOCK_GOAL)
    glDepthFunc(GL_LEQUAL); // to avoid z-fighting
  glColor4f(red, green, blue, alpha);
  glCallList(block_DL+type);
  if (type == BLOCK_DIRECTIONAL || type == BLOCK_GOAL)
    glDepthFunc(GL_LESS); // restore depth func
  // draw lines
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_POLYGON_OFFSET_LINE);
  glDepthMask(false);

  glColor3f(0.0f, 0.0f, 0.0f);
  glCallList(block_DL+type);

  glDepthMask(true);
  glDisable(GL_POLYGON_OFFSET_LINE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void cBlock::SetColor(float r, float g, float b, float a) {
  red   = r;
  green = g;
  blue  = b;
  alpha = a;
}

void cBlock::SetColor(const cBlock& sourceBlock) {
  red   = sourceBlock.red;
  green = sourceBlock.green;
  blue  = sourceBlock.blue;
  alpha = sourceBlock.alpha;
}

void cBlock::SetAlpha(float a) {
  alpha = a;
}

void cBlock::SetErasable(bool er) {
  erasable = er;
}

bool cBlock::GetErasable() const {
  return erasable;
}

cBlock& cBlock::operator=(const cBlock& b) {
  type = b.type;
  direction = b.direction;
  return *this;
}

bool cBlock::IsNull() const {
  return type == NULLBLOCK;
}

bool cBlock::IsType(int type_) const {
  return type == type_;
}

void cBlock::NextDir() {
  direction = (direction + 1) % 4;
}

int cBlock::GetDir() const {
  return direction;
}

// pre: ball touching block with the base
cVector cBlock::GetMoveDir(const cVector& prevDir) const {
  switch (type) {
    case NULLBLOCK: return prevDir;
    case BLOCK_GROUND:
    case BLOCK_QUAD:
    case BLOCK_HALF_QUAD:
    case BLOCK_STACK_QUAD_QUAD:
      return cVector(prevDir.x, 0.0f, prevDir.z);
  }
  return prevDir;
}

bool cBlock::TouchingUp(const cVector& point, int x, int y, int z) const {
  float modx = fmod(point.x + 0.5f, 1.0f);
  float mody = fmod(point.y + 0.5f, 1.0f);
  float modz = fmod(point.z + 0.5f, 1.0f);

  switch (type) {
  case NULLBLOCK: return false;

  case BLOCK_GROUND:
  case BLOCK_QUAD:
  case BLOCK_STACK_QUAD_QUAD:
    return true;

  case BLOCK_HALF_QUAD:
  case BLOCK_STACK_QUAD_DIR:
    return point.y < y;

  case BLOCK_SLOPE:
    if (direction == DIR_UP)
      return mody + modz < 1.0f;
    if (direction == DIR_DOWN)
      return mody < modz;
    if (direction == DIR_RIGHT)
      return mody + modx < 1.0f;
    if (direction == DIR_LEFT)
      return mody < modx;

  case BLOCK_HALF_SLOPE:
    if (mody > 0.5f)
      return false;
    if (direction == DIR_UP)
      return mody + 0.5f*modz < 0.5f;
    if (direction == DIR_DOWN)
      return 0.5f*mody < modz;
    if (direction == DIR_RIGHT)
      return mody + 0.5f*modx < 0.5f;
    if (direction == DIR_LEFT)
      return 0.5f*mody < modx;

  case BLOCK_STACK_QUAD_SLOPE:
    if (point.y < y)
      return true;
    mody -= 0.5f; // treat like half slope
    if (direction == DIR_UP)
      return mody + 0.5f*modz < 0.5f;
    if (direction == DIR_DOWN)
      return 0.5f*mody < modz;
    if (direction == DIR_RIGHT)
      return mody + 0.5f*modx < 0.5f;
    if (direction == DIR_LEFT)
      return 0.5f*mody < modx;
  }
  return false;
}

bool cBlock::TouchingSide(const cVector& point, int pdir, int tiley) const {
  float modx = fmod(point.x + 0.5f, 1.0f);
  float mody = fmod(point.y + 0.5f, 1.0f);
  float modz = fmod(point.z + 0.5f, 1.0f);

  switch (type) {
  case NULLBLOCK: return false;

  case BLOCK_GROUND:
  case BLOCK_QUAD:
  case BLOCK_STACK_QUAD_QUAD:
    return true;
  case BLOCK_HALF_QUAD:
  case BLOCK_STACK_QUAD_DIR:
    return point.y <= tiley;

  case BLOCK_SLOPE:
    if (pdir == direction)
      return false;
    if (pdir == (direction+2)%4) {
      if (direction == DIR_UP)
        return mody + modz < 1.0f;
      if (direction == DIR_DOWN)
        return mody < modz;
      if (direction == DIR_RIGHT)
        return mody + modx < 1.0f;
      if (direction == DIR_LEFT)
        return mody < modx;
    }
    else
      return true;

  case BLOCK_HALF_SLOPE:
    if (pdir == direction)
      return false;
    if (pdir == (direction+2)%4) {
      if (mody > 0.5f)
        return false;
      if (direction == DIR_UP)
        return mody + 0.5f*modz < 0.5f;
      if (direction == DIR_DOWN)
        return 0.5f*mody < modz;
      if (direction == DIR_RIGHT)
        return mody + 0.5f*modx < 0.5f;
      if (direction == DIR_LEFT)
        return 0.5f*mody < modx;
    }
    else
      return true;

  case BLOCK_STACK_QUAD_SLOPE:
    if (point.y <= tiley)
      return true;
    if (pdir == direction)
      return false;
    if (pdir == (direction+2)%4) {
      mody -= 0.5f; // treat like a half slope
      if (direction == DIR_UP)
        return mody + 0.5f*modz < 0.5f;
      if (direction == DIR_DOWN)
        return 0.5f*mody < modz;
      if (direction == DIR_RIGHT)
        return mody + 0.5f*modx < 0.5f;
      if (direction == DIR_LEFT)
        return 0.5f*mody < modx;
    }
    else
      return true;
  }
  return false;
}

float cBlock::GetFriction() const {
  if (type == NULLBLOCK)
    return 0.0f;
  if (type == BLOCK_QUAD || type == BLOCK_STACK_QUAD_QUAD || type == BLOCK_HALF_QUAD)
    return 0.00009f;
  if (type == BLOCK_GROUND)
    return 0.00006f;
  return 0.00003f;
}

cBlock cBlock::Stackable(const cBlock& upperBlock) const {
  switch (type) {
  case BLOCK_HALF_QUAD:
    if (upperBlock.IsType(BLOCK_HALF_QUAD)) // half quad + half quad
      return cBlock(BLOCK_STACK_QUAD_QUAD, upperBlock.direction);
    if (upperBlock.IsType(BLOCK_HALF_SLOPE)) // half quad + half slope
      return cBlock(BLOCK_STACK_QUAD_SLOPE, upperBlock.direction);
    if (upperBlock.IsType(BLOCK_DIRECTIONAL)) // half quad + directional
      return cBlock(BLOCK_STACK_QUAD_DIR, upperBlock.direction);
  }
  return cBlock();
}