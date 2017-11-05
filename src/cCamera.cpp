#include "cCamera.h"

const cVector cCamera::upVec(0.0f, 1.0f, 0.0f);

cCamera::cCamera() {
  yaw = pitch = 0;
  viewDir = cVector(1.0f, 0.0f, 0.0f);
  cameraChanged = false;
}

void cCamera::SetLookPoint(float x, float y, float z) {
  eyePos = cVector(x, y, z);
  cameraChanged = true;
}

void cCamera::MoveCamera(float yaw_, float pitch_) {
  yaw += yaw_; pitch += pitch_;
  if (pitch > PI/2.0f)
    pitch = PI/2.0f;
  if (pitch < 0.0f)
    pitch = 0.0f;
  viewDir.x = cos(yaw);
  viewDir.y = sin(pitch);
  viewDir.z = sin(yaw);
  viewDir.normalize();
  cameraChanged = true;
}

void cCamera::SetDistance(float dist) {
  distance = dist;
  cameraChanged = true;
}

void cCamera::UpdateCamera() {
  if (!cameraChanged)
    return;

  glLoadIdentity();
  cVector viewPnt = eyePos + viewDir*distance;
  gluLookAt(viewPnt.x, viewPnt.y, viewPnt.z,
            eyePos.x,  eyePos.y,  eyePos.z,
            upVec.x,   upVec.y,   upVec.z);
  cameraChanged = false;
}

// unused
/*
cCamera::cCamera() {
  yawn = pitch = 0;
  viewDir = cVector(1.0f, 0.0f, 0.0f);
}

void cCamera::MoveCamera(int dir, float speed) {
  if (dir == CMOVE_FORWARD) {
    eyePos += cVector::normalize(viewDir) * speed;
  }
  else if (dir == CMOVE_BACK) {
    eyePos -= cVector::normalize(viewDir) * speed;
  }
  else if (dir == CMOVE_RIGHT) {
    cVector mDir = cVector::cross(upVec, viewDir);
    eyePos -= cVector::normalize(mDir) * speed;
  }
  else if (dir == CMOVE_LEFT) {
    cVector mDir = cVector::cross(upVec, viewDir);
    mDir.normalize();
    eyePos += cVector::normalize(mDir) * speed;
  }
  else if (dir == CMOVE_FORWARD_IGY) {
    cVector mDir = viewDir; mDir.y = 0;
    eyePos += cVector::normalize(mDir) * speed;
  }
  else if (dir == CMOVE_BACK_IGY) {
    cVector mDir = viewDir; mDir.y = 0;
    eyePos -= cVector::normalize(mDir) * speed;
  }
  else if (dir == CMOVE_RIGHT_IGY) {
    cVector mDir = cVector::cross(upVec, viewDir); mDir.y = 0;
    eyePos -= cVector::normalize(mDir) * speed;
  }
  else if (dir == CMOVE_LEFT_IGY) {
    cVector mDir = cVector::cross(upVec, viewDir); mDir.y = 0;
    eyePos += cVector::normalize(mDir) * speed;
  }
}

void cCamera::SpinCamera(float y, float p) {
  yaw += y; pitch += p;
  viewDir.x = cos(yaw);
  viewDir.y = sin(pitch);
  viewDir.z = sin(yaw);
}

void cCamera::SetCamera() {
  glLoadIdentity();

  cVector viewPnt = eyePos + viewDir;
  gluLookAt(eyePos.x,  eyePos.y,  eyePos.z,
            viewPnt.x, viewPnt.y, viewPnt.z,
            upVec.x,   upVec.y,   upVec.z);
}*/