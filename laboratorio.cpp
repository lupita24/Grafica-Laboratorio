#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 600


int opcion ;

using namespace std;

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);
}

/************DIBUJO DE POLIGONO***************/
void polygons(int puntos)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	glLoadIdentity();
	float angulo;
	vector<float> n_x;
	vector<float> n_y;
	angulo=4*asin(1)/puntos;
	float theta=0;
	for(int i=0 ; i<= puntos ;i+=1, theta+=angulo)
	{
		cout<<i<<" "<<theta<<endl;
		n_x.push_back(1.0*cos(theta));
		n_y.push_back(1.0*sin(theta));
	}
	
	glBegin(GL_LINES);
	for(int i=1 ; i< n_x.size();i++)
	{
		glVertex3f(n_x[i-1],n_y[i-1],0);
		glVertex3f(n_x[i],n_y[i],0);
	}	
	glEnd();
	glFlush();
}

/*************BIDUJO DE LIINEA CON PUNTOS - METODO PUNTO MEDIO***************/
void line_with_point(int x0, int x1, int y0, int y1)
{
	
	int dx = x1 - x0, dy = y1 - y0;
    int iterax = 1, iteray = 1;

    if(dx < 0) //Si el x1 es menor que x0
    {
      dx = -dx; iterax = -1;
    }

    if(dy < 0) //Si el y1 es menor que y0
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


/****************DIBUJO DE CIRCULO**********************/


void draw_image_point(int cx, int cy, int x, int y){
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
    draw_image_point(cx, cy, x, y);
    while(y > x){
        if(d < 0){
            d = d + 2*x + 3;
            x = x + 1;}
        else{
            d = d + 2*(x - y) + 5;
            x = x + 1;
            y = y - 1;}
        draw_image_point(cx, cy, x, y);
    }
}

void draw_circle(int radio){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    circle(0,0, radio);
}


/**********************DIBUJO DE ELIPSE****************************/


void ellipse_points(const int& x, const int& y, const int&cx, const int& cy){
		
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
	/* Valores iniciales */
	x = 0;
	y = b;
	d1 = b * b - a * a * b + a * a / 4.0;
	ellipse_points(x+cx, y+cy,cx,cy); /* Simetria de orden 4 */
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
		ellipse_points(x+cx, y+cy,cx,cy);
	}

		d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	
	while(y > 0){
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
		ellipse_points(x+cx, y+cy,cx,cy);
	}
}

/********************DIBUJO DE HIPERBOLA**************************/
void hyperbole(int escala)
{
	float y,x;
	float a1=12;
	float b1 = 9;
	glColor3f (1, 1, 0);

	glBegin (GL_POINTS);
	for ( x = -(escala); x <escala; x++)     // Horizontal axis hyperbola
	{  
		y = a1 * sqrt (1 + (x*x)/(b1*b1));	
		glVertex2f (x,  y);
		glVertex2f (x, -y);
	}
	glEnd ();

	glColor3f (1, 0.4, 0.4);                    // Vertical axis hyperbola

	glBegin (GL_POINTS);
	for ( y = -(escala); y < escala; y++)  
	{     
		x = a1 * sqrt (1 + (y*y)/(b1*b1));
		glVertex2f ( x, y);
		glVertex2f (-x, y);
	}
	glEnd();
	glFlush();
}

void myDisplay() 
{
	 switch ( opcion )
      {
         case 1:
            polygons(6);
            glFlush();
            break;
         case 2:
            line_with_point(90,10,30,100);
            glFlush();
            break;
         case 3:
            draw_circle(250);
           	glFlush(); 
            break;
         case 4:
            draw_ellipse(50,50,80,50);
           	glFlush(); 
            break;
         case 5:
            hyperbole(100);
           	glFlush();
            break;
      }	
}

int main(int argc, char **argv)
{
	printf( "Ingresa la opcion que desee\n");
	printf( "1 - Dibujo de poligono\n");
	printf( "2 - Linea con puntos\n");
	printf( "3 - Dibujo de circulo\n");
	printf( "4 - Dibujo de elipse\n");
	printf( "5 - Dibujo de hiperbola\n");
	scanf("%d", &opcion);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Opengl's graphics");
	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
