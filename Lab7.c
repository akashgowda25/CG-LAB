#include<stdio.h>
#include<GL/glut.h>
float v[4][3]={{0.0,0.0,1.0},{0.0,1.0,0.0},{-1.0,-0.5,0.0},{1.0,-0.5,0.0}};
float color[4][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,1.0}};
int m;
void triangle(float *va,float *vb,float *vc)
{
  glBegin(GL_TRIANGLES);
  glVertex3fv(va);
  glVertex3fv(vb);
  glVertex3fv(vc);
}

void tetra(float *a,float *b, float *c,float *d)
{
  glColor3fv(color[0]);
   triangle(a,b,c);
  glColor3fv(color[1]);
   triangle(a,c,d);
  glColor3fv(color[2]);
   triangle(a,b,d);
  glColor3fv(color[3]);
   triangle(b,d,c);
}

void divide_tetra(float *a,float *b,float *c, float *d,int m)
{
  float mid[6][3];
  int j;
  if(m>0)
  {
      for(j=0;j<3;j++) mid[0][j]=(a[j]+b[j])/2;
      for(j=0;j<3;j++) mid[1][j]=(a[j]+c[j])/2;
      for(j=0;j<3;j++) mid[2][j]=(a[j]+d[j])/2;
      for(j=0;j<3;j++) mid[3][j]=(b[j]+c[j])/2;
      for(j=0;j<3;j++) mid[4][j]=(c[j]+d[j])/2;
      for(j=0;j<3;j++) mid[5][j]=(b[j]+d[j])/2; 
      divide_tetra(a,mid[0],mid[1],mid[2],m-1);
      divide_tetra(mid[0],b,mid[3],mid[5],m-1);
      divide_tetra(mid[1],mid[3],c,mid[4],m-1);
      divide_tetra(mid[2],mid[5],mid[4],d,m-1);
   }
else
   {
     tetra(a,b,c,d);
}
}
void display()
{
  //glClearColor(1,1,1,1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  divide_tetra(v[0],v[1],v[2],v[3],m);
  glEnd();                   
  glFlush();
}
 void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
{
		glOrtho(-2.0,2.0,-2.0 *(GLfloat)h/ (GLfloat)w, 2.0 *(GLfloat) h /(GLfloat) w,-10.0,10.0);
}
	else
{
		glOrtho(-2.0*(GLfloat)w / (GLfloat)h,2.0 *(GLfloat)w / (GLfloat) h,-2.0,2.0,-20.0,-20.0);
  
   }
}
int main(int argc,char **argv)
{
  printf("Enter no of division\n");
  scanf("%d",&m);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Tetrahedron 4MT19CS104");
  glClearColor(1,1,1,1);
  glutDisplayFunc(display);
  glutReshapeFunc(myReshape);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
