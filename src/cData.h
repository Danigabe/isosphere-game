#ifndef ISOSPHERE_CDATA_H
#define ISOSPHERE_CDATA_H

#include "cTexture.h"
#include "Globals.h"

enum ImageArray {
  //Image identifiers
  IMG_FONT,

  //Image array size
  NUM_IMG
};

class cData
{
public:
  cData();
  ~cData();

  int  GetID(int img);
  void GetSize(int img, int* w, int* h);
  bool LoadImage(int img, char* filename, int type = GL_RGBA);
  bool LoadImageNearest(int img, char* filename, int type = GL_RGBA);

private:
  cTexture texture[NUM_IMG];
};

#endif