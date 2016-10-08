#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <stdio.h>


using namespace std;
#define WIDTH 500
#define HEIGHT 500
int n_puntos;

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-WIDTH/2, WIDTH, -HEIGHT/2, HEIGHT);
}
void reshape(int WIDTH, int HEIGHT)
{
	glViewport(1, 1, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);//proyeccion ortogonal
	glMatrixMode(GL_MODELVIEW);
}

void polygons(int puntitos)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	glLoadIdentity();
	float angulo;
	vector<float> n_x;
	vector<float> n_y;
	angulo=4*asin(1)/puntitos;
	float theta=0;
	for(int i=0 ; i<= puntitos ;i+=1, theta+=angulo)
	{
		n_x.push_back(1.0*cos(theta));
		n_y.push_back(1.0*sin(theta));
	}
	
	glBegin(GL_LINES);
	for(int i=1 ; i< n_x.size();i++)
	{
		glVertex3f(n_x[i],n_y[i],0);
	}	
	glEnd();
	glFlush();
}

void lines_with_points(int x0, int x1, int y0, int y1)
{
	int dx = x1 - x0, dy = y1 - y0;
    int iterax = 1, iteray = 1;

    if(dx < 0)//Si el x1 es menor que x0
    {
      dx = -dx; iterax = -1;
  	}

    if(dy < 0)//Si el y1 es menor que y0
    {
      dy = -dy; iteray = -1;
    }

    int x = x0, y = y0;
    int d, incE, incNE;

    glBegin(GL_POINTS);
    glVertex2i(x0, y0);
    if(dx > dy)//Eje x
    {
      d = 2*dy - dx;
      incE = 2*dy;
      incNE = 2*(dy - dx);
      while(x != x1)
      {
        x = x + iterax;
        if(d < 0) d = d + incE;
        else
        {
          y = y + iteray;
          d = d + incNE;
        }
        glVertex2i(x, y);
      }
    }
    else//Eje y
    {
      d = 2*dx - dy;
      incE = 2*dx;
      incNE = 2*(dx - dy);
      while(y != y1)
      {
        y = y + iteray;
        if(d < 0) d = d + incE;
        else
        {
          x = x + iterax;
          d = d + incNE;
        }
        glVertex2i(x, y);
      }
    }
    glEnd();
}


void drawPuntosImagen(int cx, int cy, int x, int y){
    glBegin(GL_POINTS);
        glVertex2i(cx + x, cy + y);
        glVertex2i(cx + y, cy + x);
        glVertex2i(cx + y, cy - x);
        glVertex2i(cx + x, cy - y);
        glVertex2i(cx - x, cy - y);
        glVertex2i(cx - y, cy - x);
        glVertex2i(cx - y, cy + x);
        glVertex2i(cx - x, cy + y);
    glEnd();
}


void circle(int cx, int cy, int radio){
    int x = 0, y = radio, d = 1 - radio;
    drawPuntosImagen(cx, cy, x, y);
    while(y > x){
        if(d < 0){
            d = d + 2*x + 3;
            x = x + 1;}
        else{
            d = d + 2*(x - y) + 5;
            x = x + 1;
            y = y - 1;}
        drawPuntosImagen(cx, cy, x, y);
    }
}

void drawCircle(int radio){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    circle(0,0, radio);
}

void ellipse_point(const int& x, const int& y, const int&cx, const int& cy)
{
	
	int difx = abs(cx-x);
	int dify = abs(cy-y);
		
	glBegin(GL_POINTS);
	glVertex2i( cx + difx, cy + dify);//glVertex2i( x, y);
	glVertex2i( cx + difx, cy-dify);
	glVertex2i(cx -difx, cy+dify);
	glVertex2i(cx-difx, cy-dify);
	glEnd();
		
}
	
void draw_ellipse(const int& cx, const int& cy, const int& a, const int& b)
{
	int x,  y;
	float d1, d2;
	/* valores iniciales  */
	x = 0;
	y = b;	
	d1 = b * b - a * a * b + a * a / 4.0;
	ellipse_point(x+cx, y+cy,cx,cy); /*Simetria de orden 4 */
	while(a * a * (y - 0.5) > b * b * (x + 1))
	{
		/* Region 1 */
		if (d1 < 0)
		{
			d1 = d1 + b * b * (2 * x + 3);
			x++; 
		}
		  else
		{
			d1 = d1 + b * b * (2 * x + 3) + a * a * (-2 * y + 2);
			x++;
			y--;
		}
	}
	
	d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	
	while(y > 0)
	{
		/* Region 2 */
		if (d2 < 0)
		{
			d2 = d2 + b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++;
			y--;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		}
		else
		{
			d2 = d2 + a * a * (-2 * y + 3);
			y--;
		}
		ellipse_point(x+cx, y+cy,cx,cy);
	}
}


void myDisplay() {
	draw_ellipse(10,40,40,10);
	//polygons(4);
	glFlush();
	glutReshapeFunc(reshape);
	
}

int main(int argc, char **argv)
{
	printf( "Ingresa el numero de puntos\n");
	scanf("%d", &n_puntos);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Guadalupe's graphics");
	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
