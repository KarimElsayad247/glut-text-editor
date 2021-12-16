#define FREEGLUT_LIB_PRAGMAS 1
#define FREEGLUT_STATIC 1

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define HORIZONTAL_LETTER_WIDTH 0.5

#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

typedef vector<double> vertix;
typedef vector<vertix> vertexVector;

/* POSSIBLE ARCHITECTURE:
 * - create 26 (or how many characters there is) letter objects, each containing
 *   their own draw function. 
 * - Create an array containing references to each of these characters
 * - Create a buffer that will contain a copy of the reference of the letter to be drawn
 *   in a certain position. basically divide the view port into blocks
 * - when a letter gets drawn, copy reference to letter to approprite position in buffer
 * - a loop goes over all buffer blocks and draws characters on the screen.
*/

class Letter {
private:
	GLuint listID;
public:
	vector<vertix> points;
	Letter(vector<vertix> &p);
	void draw(double x, double y);
};

Letter::Letter(vector<vertix> &p) {
	points = p;
	listID = glGenLists(1);
	glNewList(listID, GL_COMPILE);
	draw(0, 0);
	glEndList();
}

// This draw the character to an arbitrary position decided by caller.
// Useful for creating a buffer (array of letters) that calls draw on all its contents
void Letter::draw(double x, double y) {
	glBegin(GL_LINES);
	{
		for (vector<double> p : points) {
			glVertex2d(x + p[0], y + p[1]);
		}
	}
	glEnd();
}

// TODO: Change character offset to an array containing horizontal start location
// of each character.
double characterOffset;
Letter* letterToDraw;

vertexVector letterPointsA = {
	vertix {0, 0},
	vertix {0.1, 0.2},
	vertix {0.1, 0.2},
	vertix {0.25, 0.5},
	vertix {0.25, 0.5},
	vertix {0.4, 0.2},
	vertix {0.4, 0.2},
	vertix {0.5, 0},
	vertix {0.1, 0.2},
	vertix {0.4, 0.2}
};

vertexVector letterB = {

};

vertexVector letterPointsC = {
	vertix {0.5, 0},
	vertix {0, 0},
	vertix {0, 0},
	vertix {0, 0.5},
	vertix {0, 0.5},
	vertix {0.5, 0.5},
};



vertexVector letterD = {

};

vertexVector letterE = {

};

vertexVector letterF = {

};

Letter A = Letter(letterPointsA);
Letter C = Letter(letterPointsC);

vector<Letter*> allLetters = {
	&A,
	&C
};

void init() {
	letterToDraw = allLetters[0];
	characterOffset = 0;
}

void renderCharacter(char c) {
	characterOffset += HORIZONTAL_LETTER_WIDTH;
	c = toupper(c);
	switch (c) {
	case 'A':
		letterToDraw = allLetters[0];
		break;
	case 'C':
		letterToDraw = allLetters[1];
		break;
	}
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	letterToDraw->draw(0, 0);

	glEnd();
	glutSwapBuffers();
}

void keyPressHandler(unsigned char c, int x, int y) {

	if (isalpha(c)) {
		renderCharacter(c);
	}

	switch(c) {
	case 27:
		cout << "Exiting" << endl;
		exit(EXIT_SUCCESS);
		break;
	}
}

void specialKeyFunc(int key, int x, int y) {

}

void mouse(int a, int b, int c, int d) {

}

void timer(int value) {
	glutTimerFunc(16, timer, 0);
	glutPostRedisplay();
}

void test() {

}


void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 2.0, 0.0, 2.0, -1.0, 1.0);
	cout << w << " " << h << endl;
}

int main(int argc, char** argv) {
	int mode = GLUT_RGB | GLUT_DOUBLE;
	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Simple");
	init();
	test();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressHandler);
	glutSpecialFunc(specialKeyFunc);
	glutMouseFunc(mouse);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}