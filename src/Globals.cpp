#include "Globals.h"
#include <sstream>
#include "cGame.h"

bool fequals(float a, float b, float delta) {
  float dif = abs(a - b);
  return dif < delta;
}

void drawRect(int x, int y, int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,-1,1);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glBegin(GL_QUADS);
    glVertex2i(x,   y);
    glVertex2i(x+w, y);
    glVertex2i(x+w, y+h);
    glVertex2i(x,   y+h);
  glEnd();

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

const int FONT_TEXTURE_SIZE = 64;
const int CHARS_PER_ROW     = 7;

const int CHAR_SIZE  = 8;
const int CHAR_A     = 0;
const int CHAR_COLON = 26;
const int CHAR_SPACE = 27;
const int CHAR_ZERO  = 28;

int getchar(char c) {
  if ('A' <= c && c <= 'Z')
    return CHAR_A + (c - 'A');
  if ('a' <= c && c <= 'z')
    return CHAR_A + (c - 'a');
  if ('0' <= c && c <= '9')
    return CHAR_ZERO + (c - '0');
  if (c == ':')
    return CHAR_COLON;

  return CHAR_SPACE;
}

void write(const std::string& text, int x, int y, float scale) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,-1,1);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, cGame::Data.GetID(IMG_FONT));
    glBegin(GL_QUADS);
    int desp = 0;
    for (int i = 0; i < text.size(); ++i) {
      int letter = getchar(text[i]);
      int x = letter % CHARS_PER_ROW;
      int y = letter / CHARS_PER_ROW;

      const float CSIZE = CHAR_SIZE   / (float)FONT_TEXTURE_SIZE;
      float tx0 = (x * (CHAR_SIZE+1)) / (float)FONT_TEXTURE_SIZE;
      float tyf = (y * (CHAR_SIZE+1)) / (float)FONT_TEXTURE_SIZE;
      float txf = tx0 + CSIZE;
      float ty0 = tyf + CSIZE;

      glTexCoord2f(tx0, ty0); glVertex2i(desp,           0);
      glTexCoord2f(txf, ty0); glVertex2i(desp+CHAR_SIZE, 0);
      glTexCoord2f(txf, tyf); glVertex2i(desp+CHAR_SIZE, CHAR_SIZE);
      glTexCoord2f(tx0, tyf); glVertex2i(desp,           CHAR_SIZE);
      desp += CHAR_SIZE;
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

std::string intToString(int n) {
  std::stringstream ss;
  ss << n;
  return ss.str();
}