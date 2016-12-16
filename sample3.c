#include<stdlib.h>
#include<math.h>
#include <GL/glut.h>
static GLfloat ang = 0.0;

void display(void)
{  
int i=0, x = 20;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  	glRotatef(ang, 0.0, 0.0, 1.0); /*横*/
  glBegin(GL_LINE_LOOP);
	for(i = 0;i < 360; i++){
		double rad = i/180.0*3.141592;
		glVertex2d(x*cos(rad), x*sin(rad));
	}
  glEnd();
  glFlush();
  glPopMatrix();
  glutSwapBuffers();  
}

void simu(void)
{
  ang = ang + 1.0; /*回転速度*/
  if ( ang > 360.0 )
  	ang = ang - 360.0;
  glutPostRedisplay();
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
  glViewport( 0, 0, w, h );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
  switch (button) {
     case GLUT_LEFT_BUTTON:
     	if ( state == GLUT_DOWN)
     		glutIdleFunc(simu);
     	break;
     case GLUT_RIGHT_BUTTON:
		if ( state == GLUT_DOWN)
     		glutIdleFunc(NULL);
     	break; 
     default:
     	break; 
  }
}

void keyboard(unsigned char key, int x, int y)
{
  if ( key == '\x1b') exit(0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (400, 400);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);
  init();
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutDisplayFunc(display);
    glutMainLoop();
  return 0;
} 
