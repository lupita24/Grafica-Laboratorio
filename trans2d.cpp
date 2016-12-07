#include "punto.h"

vector<Punto> puntos;
Punto * centro = NULL;

void raton(int boton,int estado,int x,int y)
{
  if(boton == GLUT_LEFT_BUTTON)
  {
    if(estado == GLUT_UP)
    { 
      band = false;
      punto.x = x;
      punto.y = ALTO-y;
      puntos.push_back(punto);

      glBegin(GL_POINTS);
        glVertex2d(punto.x,punto.y);
      glEnd();
      cout<<punto.x<<" "<<punto.y<<endl;
    }
  }
  glutPostRedisplay();
}

void edgedetect(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)   
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)     
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;   
            x=x1;
            for(i=y1;i<y2;i++)       
            {                             
                                          
                        if(x<le[i])       
                                    le[i]=x;
                                            
                        if(x>re[i])         
                                    re[i]=x;
                        x+=mx;            
            }                             
}

void drawpixel(int x,int y,int color)
{
    if(color == 0)
    {
       glColor3f(1.0,0.0,0.0);
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd();
    }
    else
    if(color == 1){
       glColor3f(0.0,1.0,0.0);
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd();
    }
     else
    if(color == 2){
       glColor3f(0.0,1.0,1.0);
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd();
    }else
    if(color == 1){
       glColor3f(1.0,0.0,1.0);
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd();
    }      
}

void scanfill(int color)
{
            int le[500],re[500];
            int i,y;
            for(i=0;i<500;i++)  
            {
                        le[i]=500;
                        re[i]=0;
            }
            int tam=(int)puntos.size();
            for(int i=0;i<tam-1;i++)
            {
              edgedetect(puntos[i].x,puntos[i].y,puntos[i+1].x,puntos[i+1].y,le,re);   
            }
            edgedetect(puntos[tam].x,puntos[tam].y,puntos[0].x,puntos[0].y,le,re);

        for(y=0;y<500;y++)       
        {
           if(le[y]<=re[y])       
                        for(i=le[y]+1;i<re[y];i++) 
                                    drawpixel(i,y,color);     
        }                                               
}

void pintar()
{
    int color;
    cout<<"0 - rojo"<<endl;
    cout<<"1 - verde"<<endl;
    cout<<"2 - celeste"<<endl;
    cout<<"3 - rosado"<<endl;
    cout<<"escoge el color"<<endl;
    cin>>color;
    glClear(GL_COLOR_BUFFER_BIT);
    int tam=(int)puntos.size();
    glBegin(GL_LINE_LOOP); 
    for(int i=0;i<tam;i++)
    {
        glVertex2f(puntos[i].x,puntos[i].y);
    }
    glEnd();
    scanfill(color);
    glFlush();
}

void trasladar(void){
  int distX,distY;
  int cambioX, cambioY;
  int XP,YP;
  cout<<"Traslaccion de X en : ";
  cin>>distX;
  cout<<"Traslaccion de Y en : ";
  cin>>distY;
  cout<<endl;

  (*centro).x += distX;
  (*centro).y += distY;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();

  XP = puntos[0].x;
  YP = puntos[0].y;

  glBegin(GL_LINES);
  for(int i=1;i<tam;i++)
  {
    cambioX = XP + distX;
    cambioY = YP + distY;

    puntos[i-1].x = cambioX;
    puntos[i-1].y = cambioY;
      
    glVertex2d( cambioX , cambioY );
    glVertex2d(puntos[i].x + distX ,puntos[i].y + distY);

    XP = puntos[i].x;
    YP = puntos[i].y;
  }
    puntos[tam-1].x += distX;
    puntos[tam-1].y += distY;

    glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );
    glVertex2d(puntos[0].x ,puntos[0].y);
  glEnd();
  return;

}

void escalar(void){
  float escX,escY;
  int XP, YP,X2P,Y2P;
  int actX, actY;

  
  cout<<"escala en X: ";
  cin>>escX;
  cout<<"escala en Y: ";
  cin>>escY;
  cout<<endl;

  if(escX == 0 || escY == 0){
    escX = 1;
    escY = 1;
    cout<<"El valor 0 no es valido"<<endl;
  }

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();

  actX = puntos[0].x;
  actY = puntos[0].y;

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++)
    {

      XP = actX * escX + (*centro).x * (1 - escX);
      YP = actY * escY + (*centro).y * (1 - escY);

      puntos[i-1].x = XP;
      puntos[i-1].y = YP;

      X2P = puntos[i].x * escX + (*centro).x * (1 - escX);
      Y2P = puntos[i].y * escY + (*centro).y * (1 - escY); 

      glVertex2d(XP ,YP);
      glVertex2d(X2P ,Y2P);

      actX = puntos[i].x;
      actY = puntos[i].y;
    }

    puntos[tam-1].x = actX * escX + (*centro).x * (1 - escX);
    puntos[tam-1].y = actY * escY + (*centro).y * (1 - escY);

    glVertex2d(puntos[0].x ,puntos[0].y);
    glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );

    (*centro).x = (*centro).x * escX + (*centro).x * (1 - escX);
    (*centro).y = (*centro).y * escY + (*centro).y * (1 - escY);
  glEnd();

}


void rotar(void){
  int angulo;
  int XP, YP,X2P,Y2P;
  int actX, actY;

  cout<<"Angulo nuevo: "<<endl;
  cin>>angulo;
  cout<<endl;

  angulo = (angulo * pi) / 180;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();
  actX = puntos[0].x;
  actY = puntos[0].y;

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++){
      XP = (actX * cos(angulo)) + (-sin(angulo) * actY) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
      YP = (actX * sin(angulo)) + (cos(angulo) * actY) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

      puntos[i-1].x = XP;
      puntos[i-1].y = YP;

      X2P = (puntos[i].x * cos(angulo)) + (-sin(angulo) * puntos[i].y) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
      Y2P = (puntos[i].x * sin(angulo)) + (cos(angulo) * puntos[i].y) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

      glVertex2d(XP ,YP);
      glVertex2d(X2P ,Y2P);

      actX = puntos[i].x;
      actY = puntos[i].y;

    }

    puntos[tam-1].x = (actX * cos(angulo)) + (-sin(angulo) * actY) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
    puntos[tam-1].y = (actX * sin(angulo)) + (cos(angulo) * actY) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

    glVertex2d(puntos[0].x ,puntos[0].y);
    glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );

    (*centro).x = ((*centro).x * cos(angulo)) + (-sin(angulo) * (*centro).y) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
    (*centro).y = ((*centro).x * sin(angulo)) + (cos(angulo) * (*centro).y) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

  glEnd();
  return;

}



void menu(){
  int opcion=6;
       while(opcion != 5)
        {
          glFlush();
          cout<<"Menu:"<<endl;
          cout<<"1) Traslaccion"<<endl;
          cout<<"2) Escalamiento"<<endl;
          cout<<"3) Rotacion"<<endl;
          cout<<"4) Pintado"<<endl;
          cout<<"5) Salir"<<endl;
          cout<<endl;
          cout<<"Escoge una opcion: ";
          cout<<endl;
          cin>>opcion;

          if(opcion == 1)
          {
            trasladar();
          }
          else if(opcion == 2){
            escalar();
          }
          else if(opcion ==3){
            rotar();
          }
          else if(opcion ==4){
            pintar();
          }
        }
        return;
  glFlush();
}

void Dibuja(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);   
  glLineWidth(2.0);
  int tam = puntos.size();

  glBegin(GL_LINES);
    for(int i=1;i<tam;i++){
      glVertex2d(puntos[i-1].x,puntos[i-1].y);
      glVertex2d(puntos[i].x,puntos[i].y);
    }
  glEnd();

    if(tam > 2 ){
      if(distance(puntos[0].x ,puntos[0].y ,puntos[tam-1].x,puntos[tam-1].y)){
        glBegin(GL_LINES);
          glVertex2d(puntos[0].x,puntos[0].y);
          glVertex2d(puntos[tam-1].x,puntos[tam-1].y);
        glEnd();

        glutMouseFunc(NULL);
        cerrado = true;   

        glFlush();
        menu();
        exit(0);
      }
    }
  glFlush();
}

void inicializa(){  
  glClearColor(0.0,0.0,0.0,0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,ANCHO,0,ALTO);
}

int main(int argc, char **argv){  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(ANCHO,ALTO);
  glutInitWindowPosition(100,50);
  glutCreateWindow("TRANFORMACIONES"); 
  inicializa();

  glutDisplayFunc(Dibuja);
  glutMouseFunc(raton);

  glutMainLoop();

return 0;
}
