#ifndef ISOSHPERE_CCAMERA_H
#define ISOSHPERE_CCAMERA_H

#include "Globals.h"
#include "cVector.h"

// la camara rota alrededor de un punto fijo. para simplificar,
// se considera que el punto fijo es eyePos y que la posicion
// de la camara es eyePos + viewDir*distance
class cCamera {
public:
  cCamera();
  ~cCamera() { }

  void SetLookPoint(float x, float y, float z);
  void MoveCamera(float yaw_, float pitch_);
  void SetDistance(float dist);
  void UpdateCamera();

  cVector GetLookAt() const { return eyePos; }
  cVector GetViewDir() const { return -viewDir; }
  cVector GetPosition() const { return eyePos + viewDir*distance; }
  cVector GetUpVector() const { return upVec; }
  bool GetMoved() const { return cameraChanged; }

private:
  static const cVector upVec;
  float distance;
  float yaw, pitch;
  cVector  eyePos;
  cVector viewDir;
  bool cameraChanged;
};

// unused
/*
enum CameraMoveDirection {
  CMOVE_FORWARD,
  CMOVE_BACK,
  CMOVE_RIGHT,
  CMOVE_LEFT,
  // Ignore y angle of viewDir
  CMOVE_FORWARD_IGY,
  CMOVE_BACK_IGY,
  CMOVE_RIGHT_IGY,
  CMOVE_LEFT_IGY
};

class cCamera {
public:
  cCamera();
  ~cCamera() { }

  void MoveCamera(int dir, float speed);
  void SpinCamera(float yaw, float pitch);
  void SetCamera();

  cVector GetLookAt() const { return eyePos + viewDir; }
  cVector GetViewDir() const { return viewDir; }
  cVector GetPosition() const { return eyePos; }
  cVector GetUpVector() const { return upVec; }

private:
  static const cVector upVec;
  float yaw, pitch;
  cVector  eyePos;
  cVector viewDir;
};*/

#endif