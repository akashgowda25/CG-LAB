#include <stdio.h>
#include <GL/glut.h>

float x1 , y01 , x2 , y2 , x3 , y3 , x4 , y4;
float le[1000] , re[1000];

void edge_detect(float x1, float y01, float x2, float y2)
{
	float mx , x;
	int i;
	
	if((y2-y01)!=0)
	{
		mx = (x2-x1)/(y2-y01);
	}
	
	x = x1;
	
	for(i=y01 ; i<=y2 ; i++)
	{
		if(x<=le[i])
			le[i] = x;
		else
			re[i] = x;
			
		x+=mx;
	}
}

void scanfill(float x1, float y01, float x2, float y2, float x3, float y3, float x4, float y4)
{
	int i , y;
	
	for(i=y01 ; i<y3 ; i++)
	{
		le[i] = x1;
		re[i] = x1;
	}
	
	edge_detect(x1 , y01 , x2 , y2);
	edge_detect(x2 , y2 , x3 , y3);
	edge_detect(x4 , y4 , x3 , y3);
	edge_detect(x1 , y01 , x4 , y4);
	
	for(y=y01 ; y<y3 ; y++)
	{
		for(i=le[y] ; i<=re[y] ; i++)
		{
			glColor3f(1.0 , 1.0 , 0.0);
			glBegin(GL_POINTS);
			glVertex2f(i , y);
			glEnd();
			//glFlush();
		}
	}
}

void sub_menu(int ch)
{
	switch(ch)
	{
		case 1 :  glColor3f(0.0 , 0.0 , 0.0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(x1 , y01);
				glVertex2f(x2 , y2);
				glVertex2f(x3 , y3);
				glVertex2f(x4 , y4);
				glEnd();
				glFlush();
				break;
				
		case 2 :  scanfill(x1 , y01 , x2 , y2 , x3 , y3 , x4 , y4);
				glColor3f(0.0 , 0.0 , 0.0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(x1 , y01);
				glVertex2f(x2 , y2);
				glVertex2f(x3 , y3);
				glVertex2f(x4 , y4);
				glEnd();
				glFlush();
				break; 
	}
}

void main_menu(int ch)
{
	switch(ch)
	{
		case 3 :  exit(0);
				break;
	}
}

void display(void)
{
	x1 = 400.0 , y01 = 400.0 , x2 = 200.0 , y2 = 600.0 , x3 = 400.0 , y3 = 800.0 , x4 = 600.0 , y4 = 600.0;
	glFlush();
}

void main(int argc , char **argv)
{
	glutInit(&argc , argv);
	glutInitWindowSize(700 , 700);
	glutInitWindowPosition(0 , 0);
	glutCreateWindow("SCANLINE FILL - 4MT19CS094");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0 , 1.0 , 1.0 , 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	int submenu = glutCreateMenu(sub_menu);
	glutAddMenuEntry("Draw polygon" , 1);
	glutAddMenuEntry("Fill polygon" , 2);
	
	glutCreateMenu(main_menu);
	glutAddSubMenu("Program to.." , submenu);
	glutAddMenuEntry("Quit" , 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0 , 1000.0 , 0.0 , 1000.0);
	glutDisplayFunc(display);
	glutMainLoop();
}
