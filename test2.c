#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#define PI 3.14159265258979
#define G 0.098
#define e 0.9
static GLfloat w=0;
double leg_deg=0,rotate=1;
int top=200,bottom=-200,left=-200,right=200,r=5;
double x=100,x2=0,y=70,y2=0,m=3,m2=6;
double i1=0, i2=0,i3=180;

struct data{
double m;
double r;
double vx;
double vy;
};
struct data obj[2]={
	{3,10,-2,0},
	{6,18,0,0}
};

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
int r3=95;
double a=0,b=0,c=0;
double distance,disx,disy;


glPushMatrix();//ground
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_LINES);
for(i1=0;i1<360;i1+=10){
	glVertex2d(left, bottom+1);
	glVertex2d(right, bottom+1);
	glVertex2d(left, bottom+10);
	glVertex2d(right, bottom+10);
}
glEnd();
glFlush();
glPopMatrix();

glPushMatrix();//ball
glColor3f(1.0, 1.0, 0.0);
glRotatef(w, 0.0, 0.0, 0.0);
glBegin(GL_TRIANGLE_STRIP);
for(i1=20;i1<340;i1+=10){
	i2 = i1 + 10;
	glVertex2d(x, y);
	glVertex2d(x+obj[0].r*cos((i1+w)*PI/180),y+obj[0].r*sin((i1+w)*PI/180));
	glVertex2d(x+obj[0].r*cos((i2+w)*PI/180),y+obj[0].r*sin((i2+w)*PI/180));
}
glEnd();
glFlush();
glPopMatrix();

glPushMatrix();//leg
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_LINES);
glVertex2d(-r3,0);
glVertex2d(x2,y2);
glEnd();
glFlush();
glPopMatrix();

glPushMatrix();//foot
glColor3f(0.0, 1.0, 1.0);
glBegin(GL_TRIANGLE_STRIP);
x2=r3*cos(i3*PI/180)-r3;
y2=r3*sin(i3*PI/180);
for(i1=0, i2=10;i2<=360;i1+=10, i2+=10){
glVertex2d(x2,y2);
glVertex2d(x2+obj[1].r*cos(i1*PI/180),y2+obj[1].r*sin(i1*PI/180));
glVertex2d(x2+obj[1].r*cos(i2*PI/180),y2+obj[1].r*sin(i2*PI/180));
}
glEnd();
glFlush();
glPopMatrix();
glutSwapBuffers();

disx=pow((x-x2),2);
disy=pow((y-y2),2);
distance=sqrt((disx+disy));
if((r + obj[1].r) >= distance){//foot-collision or
if(obj[0].vx>0)//adjust
	x-=r+obj[1].r-distance;
else if(obj[0].vx<0)
	x+=r+obj[1].r-distance;
else if(obj[0].vy>0)
	y-=r+obj[1].r-distance;
else if(obj[0].vy<0)
	y+=r+obj[1].r-distance;
/*
vx+=sin(i3*PI/180);
vy+=cos(i3*PI/180);*/
obj[0].vx*=-1;

rotate*=-1;
	}
}

void simu(void)
{
w += 5*rotate;
if ( w == 360 )
	w=0;

if(i3 == 180)
leg_deg=1.0;
if(i3 >= 360)
leg_deg=-1.0;

i3+=leg_deg;

obj[0].vy-=G;
x += obj[0].vx;
y += obj[0].vy;

if ( x-obj[0].r < left ){
	obj[0].vx *=(-1)*e;
	x+=left-(x-obj[0].r);
	rotate=-1;
}
if( x+obj[0].r >right ){
	obj[0].vx *=(-1)*e;
	x+=right-(x+obj[0].r);
	rotate=1;
}
if( y-obj[0].r-G < bottom + 10 ){
	obj[0].vy *=(-1)*e;
	y+=bottom - (y-obj[0].r - G) + 10;
}
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
glutInitWindowSize (800, 800);
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
