#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.1416
int choice=0;
int cp[4][2]={
             {20,100},
             {30,110},
             {50,90},
             {60,100}};
int inc;
int c[4],k,n=3;
float x,y,u,blend;
float theta=0;
void main_menu(int c)
{
	switch(c)
	{
		case 1:choice=1;
		glutPostRedisplay();
		break;
		case 2:exit(0);
	}
}
void bezierCoefficients(int n,int *c)
{
   int k,i;
   for(k=0;k<=n;k++)
   {
      c[k]=1;
      for(i=n;i>=k+1;i--)
       {
        c[k]*=i;
       }        
      for(i=n-k;i>=2;i--)
      {
          c[k]/=i;
       }
   }
}
void curve()
{
    bezierCoefficients(n,c);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
    int i;
    for(u=0;u<1;u+=0.05)
    {
      x=0;
      y=0;
      for(k=0;k<=3;k++)
      {
            blend=c[k]*pow(u,k)*pow(1-u,n-k);
            x+=cp[k][0]*blend;
            y+=cp[k][1]*blend;
       }
       glVertex2f(x,y);
    }
    glEnd();
}

void animated_flag()
{
     cp[0][0]=20;
     cp[0][1]=100;
     cp[1][0]=30;
     cp[1][1]=110;
     cp[2][0]=50;
     cp[2][1]=90;
     cp[3][0]=60;
     cp[3][1]=100;
     cp[1][0]+=10*sin(theta *PI/180.0);
     cp[1][1]+=5*sin(theta *PI/180.0);
     cp[2][0]-=10*sin((theta+30)*PI/180);
     cp[2][1]-=10*sin((theta+30)*PI/180);
     cp[3][0]-=4*sin((theta) *PI/180.0);
     cp[3][1]+=sin((theta-30) *PI/180.0);
     theta+=4;
     glColor3f(0.0,1.0,0.0);
     for(inc=0;inc<5;inc++)
     {
	     glPushMatrix();
	     glTranslatef(0.0,inc,0.0);
	     curve();
	     glPopMatrix();
     }
     glColor3f(1.0,1.0,1.0);
     for(inc=5;inc<10;inc++)
     {
	     glPushMatrix();
	     glTranslatef(0.0,inc,0.0);
	     curve();
	     glPopMatrix();
     }
     glColor3f(1.0,0.5,0.0);
     for(inc=10;inc<15;inc++)
     {
	     glPushMatrix();
	     glTranslatef(0.0,inc,0.0);
	     curve();
	     glPopMatrix();
     }
     glColor3f(0.7,0.5,0.3);
     glLineWidth(5);
     glBegin(GL_LINES);
     glVertex2f(20,115);
     glVertex2f(20,40);
     glEnd();
     glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(choice==1)
	{
		animated_flag();
	}
	glutPostRedisplay();
	glutSwapBuffers();
}

void myinit()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(5.0);
	gluOrtho2D(0.0,130.0,0.0,130.0);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Bezier Curve 4MT19CS104");
	glutDisplayFunc(display);
	myinit();
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Animated Flag",1);
	glutAddMenuEntry("Quit",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

