#include <GL/glut.h>

GLfloat anguloCuboX = 0.0f;
GLfloat anguloCuboY = 0.0f;
GLint ancho, alto;
int hazPerspectiva = 0;
bool derecha = false;
bool izquierda =false;


void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(hazPerspectiva){
		gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.0f,20.0f);
	}
	else
		glOrtho(-4, 4, -4, 4, 1, 10);
	if(derecha)
		glTranslatef(2.0f, 0.0f, 0.0f);

	else if(izquierda)
		glTranslatef(-2.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	ancho = width;
	alto = height;
}

void drawCube(void)
{
	 glBegin(GL_QUADS);

        //front   rojo
	glColor3f (0.0,1.0,0.0);

        glVertex3f(1.0,1.0,1.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);


        glVertex3f(2.0,0.05,1.0);
        glVertex3f(-2.0,0.05,1.0);
        glVertex3f(-2.0,-1.0,1.0);
        glVertex3f(2.0,-1.0,1.0);

        //back blanco

//        glColor3f (1.0, 1.0, 1.0);
	glColor3f (1.0, 0.0, 1.0);
        glVertex3f(1.0,1.0,-1.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(1.0,-1.0,-1.0);

        glVertex3f(2.0,0.05,-1.0);
        glVertex3f(-2.0,0.05,-1.0);
        glVertex3f(-2.0,-1.0,-1.0);
        glVertex3f(2.0,-1.0,-1.0);

        //top azul

//        glColor3f(0.0,0.0,1.0);
	glColor3f (1.0, 0.0, 1.0);

        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,1.0,-1.0);
        glVertex3f(-1.0,1.0,-1.0);

        //bottom //celeste
//        glColor3f(0.0,1.0,1.0);
	glColor3f (1.0, 0.0, 1.0);
        glVertex3f(2.0,-1.0,1.0);
        glVertex3f(2.0,-1.0,-1.0);
        glVertex3f(-2.0,-1.0,-1.0);
        glVertex3f(-2.0,-1.0,1.0);

        //right  //rosado
  //      glColor3f(1.0,0.0,1.0);
        glColor3f (1.0, 0.0, 1.0);

        glVertex3f(2.0,0.05,1.0);
        glVertex3f(2.0,-1.0,1.0);
        glVertex3f(2.0,-1.0,-1.0);
        glVertex3f(2.0,0.05,-1.0);


        //left  //amarillo
//        glColor3f(1.0,1.0,0.0);
	glColor3f (1.0, 0.0, 1.0);
        glVertex3f(-2.0,0.05,1.0);
        glVertex3f(-2.0,-1.0,1.0);
        glVertex3f(-2.0,-1.0,-1.0);
        glVertex3f(-2.0,0.05,-1.0);

        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-0.05,1.0);
        glVertex3f(-1.0,-0.05,-1.0);
        glVertex3f(-1.0,1.0,-1.0);


        glVertex3f(0.05,-0.0,1.0);
        glVertex3f(0.05,-0.0,-1.0);
        glVertex3f(-2.0,-0.0,-1.0);
        glVertex3f(-2.0,-0.0,1.0);

    glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f);
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f);
	drawCube();

	glFlush();
	glutSwapBuffers();

	anguloCuboX+=0.1f;
	anguloCuboY+=0.1f;
}

void init()
{
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	ancho = 400;
	alto = 400;
	gluOrtho2D(0,ancho,0,alto);
}

void idle()
{
	display();
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			hazPerspectiva=1;		
			reshape(ancho,alto);
			break;
		case GLUT_KEY_DOWN:
			hazPerspectiva=0;
			reshape(ancho,alto);
			break;
		case GLUT_KEY_LEFT:
			izquierda = true;
			derecha = false;
			reshape(ancho,alto);
			break;
		case GLUT_KEY_RIGHT:
			izquierda = false;
			derecha = true;
			reshape(ancho,alto);
			break;
		case 27:	// escape
			exit(0);
			break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Cubo 3D");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutSpecialFunc(SpecialInput);
	glutMainLoop();
	return 0;
}
