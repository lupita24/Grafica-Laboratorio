#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

#define ALTO 600
#define ANCHO 400

#define pi 3.14159265

int Cordx=1000,Cordy=1000;
bool band = false;
bool cerrado = false;

bool distance(int x1 ,int y1,int x2 ,int y2){
  int distancia = sqrt(pow(x1 - x2 ,2)+pow(y1 - y2,2));
  
  if (distancia < 100) return true;
  else return false;
  return false;
}


struct Punto{
  GLdouble x;
  GLdouble y;
  Punto(){}
  Punto(float _x, float _y)
  {
    x=_x;
    y=_y;
  }
}punto;
