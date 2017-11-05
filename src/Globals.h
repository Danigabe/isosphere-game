#ifndef ISOSPHERE_GLOBALS_H
#define ISOSPHERE_GLOBALS_H

#ifdef _WIN32
  #include <windows.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

class cData;

// window constants
const float FOVY  = 45.0f;
const float ZNEAR =  0.1f;
const float ZFAR  = 25.0f;
const float SCREEN_WIDTH  = 800;
const float SCREEN_HEIGHT = 600;
const float WRATIO = SCREEN_WIDTH / SCREEN_HEIGHT;

const int MAX_LEVEL = 10;

const std::string QUAD_NAME       = "cube";
const std::string HALF_QUAD_NAME  = "little cube";
const std::string SLOPE_NAME      = "slope";
const std::string HALF_SLOPE_NAME = "little slope";
const std::string DIR_NAME        = "direction";

// shader locations
const char* const inkSh_vert = "res/inkShader.vert";
const char* const inkSh_frag = "res/inkShader.frag";

bool fequals(float a, float b, float delta = 0.0001);
// draws a rectangle in the x, y position of the screen
// of size wxh
void drawRect(int x, int y, int w, int h);
// writes a text in the screen in the position x, y of the
// screen
void write(const std::string& text, int x, int y, float scale = 1.0f);
// converts an integer to a string
std::string intToString(int n);

#endif