#include<stdio.h>
#include<GL/glut.h>
float h=0,k=0,theta;
int choice;

void draw_triangle()
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(100,100);
	glVertex2i(400,100);
	glVertex2i(250,350);
	glEnd();


}



void display_about_origin()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_triangle();
	glRotatef(theta,0,0,1);
	draw_triangle();
	glFlush();
}


void display_about_fixedpoint()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_triangle();
	glTranslatef(h,k,0);
	glRotatef(theta,0,0,1);
	glTranslatef(-h,-k,0);
	draw_triangle();
	glFlush();
}


int main(int argc, char **argv)
{
	printf("Enter 1 for Rotation about the Origin\n");
	printf("Enter 2 for Rotation about the fixed point\n");
	scanf("%d",&choice);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	if(choice==1)
	{
		glutCreateWindow("Rotation about origin_4MT19CS107\n");
		printf("enter angle of rotation\n");
		scanf("%f",&theta);
		glutDisplayFunc(display_about_origin);
	}
	else if(choice==2)
	{
		glutCreateWindow("Rotation about Fixed point_4MT19CS107\n");
		printf("enter angle of rotation\n");
		scanf("%f",&theta);
		printf("Enter pivot points");
		scanf("%f%f",&h,&k);
		glutDisplayFunc(display_about_fixedpoint);
	}

	else
	{
		printf("Invalid Choice\n");
	}
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(-500.0,500.0,-500.0,500.0);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glutMainLoop();
	return 0;
}
