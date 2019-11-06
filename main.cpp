#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h> // usleep
#define UDELAY 75000

using namespace std;

const int heliWidth = 8;
const int heliHeight = 5;

int eyepos[3] = {0,-100,0};

const int maxHeight = 100;
const int minHeight = -100;
const int maxWidth = 20;
const int minWidth = -20;

int posx = heliWidth/2+minWidth;
int posy = 0;

int dir = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};

bool gameOver = false;

void initialize(){
	cout << "Initializing Game" << endl;
	glClearColor(0.5, 0.7, 0.5, 0.0); // background color
	gameOver = false;
	dir = STOP;
	posx = heliWidth/2+minWidth;
	posy = 0;
	cout << "Game Initialized" << endl;
}

void helicopter(int xcenter,int zcenter){
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);

	glVertex3i(xcenter-heliWidth/2,0,zcenter-heliHeight/2);
	glVertex3i(xcenter+heliWidth/2,0,zcenter-heliHeight/2);
	glVertex3i(xcenter+heliWidth/2,0,zcenter+heliHeight/2);
	glVertex3i(xcenter-heliWidth/2,0,zcenter+heliHeight/2);

	glEnd();
}
void Draw(){
	helicopter(posx,posy);
}

void Input(unsigned char Key, int x, int y)
{
	switch(Key)
	{
	case ' ': dir = UP; break;
	};
}
void Logic(){
	//usleep(UDELAY*0.75);
	switch(dir)
    {
        case UP:
			if (posy < maxHeight - heliHeight/2) posy+=5;
			dir = DOWN;            
			break;
        case DOWN:
            if (posy > minHeight + heliHeight/2) posy--;
            break;
        default:
            break;
    }
}

void GameOver(){

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT); // reset the color bit, no depth
	glLoadIdentity();
	// Right-hand rule: make an L shape, thumb is x, index is y, middle finger is Z(up)
	// camera at eye(x,y,z) | center look at (0,0,0) | up vector is orientation
	gluLookAt(eyepos[0], eyepos[1], eyepos[2], 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	Draw();
	Logic();
	
	glutSwapBuffers();   // swapping frame buffer to new one
	if(!gameOver){
    	glutPostRedisplay(); // say the window must be redisplayed
	}
}
void reshape(int w,int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // remaps the new size and window
	glMatrixMode(GL_PROJECTION);	// set matrix stack to projection
	glLoadIdentity();	// resets the matrix to an identity matrix

	// used for defining a viewing volue of a 4-sided pyramid
	// set the origin to the center of the screen
	// glFrustum(left, right,bottom,top,nearVal,farVal); google the image
	// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.25, 20.0);
	// glOrtho // used for defining the viewing volume of a box
	// https://stackoverflow.com/questions/2571402/how-to-use-glortho-in-opengl	
	glOrtho(minWidth, maxWidth, minHeight, maxWidth, -1, 100);
	glMatrixMode(GL_MODELVIEW);	
}


int main(int argc, char **argv){

	glutInit(&argc, argv);
	// smoother animations, no transparent, no depth
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	int winHandle = glutCreateWindow("Main");

	glutSetWindow(winHandle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Input);

	initialize();
	glutMainLoop();
}
