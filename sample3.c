#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.14159265258979
static GLfloat w=0;
double rad,vx=-0.6,vx2=0,vy=0.90,vy2=0,sub=0,sub2=0;
int top=100,bottom=-100,left=-100,right=100,r=3,r2=6;
double x=0,x2=10,y=0,y2=10,m=3,m2=6;

void display(void)
{
int i1=0, i2=0;
double distance,disx,disy;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 1.0, 0.0);
glPushMatrix();

glRotatef(w, 0.0, 0.0, 0.0);
glBegin(GL_TRIANGLE_STRIP);
for(i1=0;i1<360;i1+=10){
	i2 = i1 + 10;
	glVertex2d(x, y);
	glVertex2d(x+r*cos(i1*PI/180),y+r*sin(i1*PI/180));
	glVertex2d(x+r*cos(i2*PI/180),y+r*sin(i2*PI/180));
}
glEnd();
glFlush();
glPopMatrix();

glPushMatrix();
glColor3f(0.0, 1.0, 1.0);
glRotatef(w, 0.0, 0.0, 0.0);
glBegin(GL_TRIANGLE_STRIP);
for(i1=0;i1<360;i1+=10){
	i2 = i1 + 10;
	glVertex2d(x2, y2);
	glVertex2d(x2+r2*cos(i1*PI/180),y2+r2*sin(i1*PI/180));
	glVertex2d(x2+r2*cos(i2*PI/180),y2+r2*sin(i2*PI/180));
}
glEnd();
glFlush();
glPopMatrix();
glutSwapBuffers();

disx=pow((x-x2),2);
disy=pow((y-y2),2);
distance=sqrt((disx+disy));
if((r + r2) >= distance){
//printf("%lf %lf\n",m/m2,m2/m);
if(vx>0)
	x-=r+r2-distance;
else if(vx<0)
	x+=r+r2-distance;
else if(vy>0)
	y-=r+r2-distance;
else if(vy<0)
	y+=r+r2-distance;
sub=vx;
sub2=vy;
vx=m2/m*vx2;
vy=m2/m*vy2;

vx2=m/m2*sub;
vy2=m/m2*sub2;
}
}

void simu(void)
{
w += 0.05;
if ( w == 360 )
	w=0;
x += vx;
y += vy;
x2 += vx2;
y2 += vy2;
	if ( x < left/2 || x > right/2 )
		vx *=(-1);
	if ( x2 < left/2 || x2 > right/2)
		vx2 *=(-1);
	if ( y > top/2 || y < bottom/2 )
		vy *=(-1);
	if( y2 > top/2 || y2 < bottom/2)
		vy2 *=(-1);
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
