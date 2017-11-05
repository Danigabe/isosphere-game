#include "cData.h"

cData::cData() {
}

cData::~cData() {
}

int cData::GetID(int img) {
  return texture[img].GetID();
}

void cData::GetSize(int img, int* w, int* h) {
  texture[img].GetSize(w,h);
}

bool cData::LoadImage(int img, char* filename, int type) {
  return texture[img].Load(filename, type);
}

bool cData::LoadImageNearest(int img, char* filename, int type) {
  return texture[img].Load(filename, type, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST, false);
}