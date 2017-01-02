#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.14159265258979
static GLfloat w=0;
double rad,x=0,y=0,a=0.08,b=0.06;
int top=100,bottom=-100,left=-100,right=100;

void display(void)
{
int i1=0, i2=0, r1 = 5, r2 = 3;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 1.0, 0.0);
glPushMatrix();
glRotatef(w, 0.0, 0.0, 0.0);
glTranslatef( x, y, 0);
glBegin(GL_TRIANGLE_STRIP);
for(i1=0;i1<360;i1+=10){
	i2 = i1 + 10;
	glVertex2d(0, 0);
	glVertex2d(r1*cos(i1*PI/180),r1*sin(i1*PI/180));
	glVertex2d(r1*cos(i2*PI/180),r1*sin(i2*PI/180));
}
glEnd();
glFlush();
glPopMatrix();

glPushMatrix();
glColor3f(0.0, 1.0, 1.0);
glRotatef(w, 0.0, 0.0, 0.0);
glTranslatef( -x, -y, 0);
glBegin(GL_TRIANGLE_STRIP);
for(i1=0;i1<360;i1+=10){
	i2 = i1 + 10;
	glVertex2d(0, 0);
	glVertex2d(r2*cos(i1*PI/180),r2*sin(i1*PI/180));
	glVertex2d(r2*cos(i2*PI/180),r2*sin(i2*PI/180));
}
glEnd();
glFlush();
glPopMatrix();
glutSwapBuffers();
}

void simu(void)
{
w += 0.05;
	if ( w == 360 )
	w=0;
x += a;
y += b;
	if ( x > right/2 || x < left/2)
	a *=(-1);
	if ( y > top/2 || y < bottom/2)
	b *=(-1);
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
glOrtho( left, right, bottom, top, -1.0, 1.0);
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
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
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
