#include <stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
using namespace std;

string text = "Hello";

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glRasterPos2i(0, 0);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    
    //iterate on string
    for(int i = 0; i < text.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y){
    cout << key << endl;
    if (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key >= '0' && key <= '9' || key == ' '){
        text += key;
    }
    else if (key == '\b'){
        text = text.substr(0, text.length() - 1);
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow ("square");
    
    init();

    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);//only switch when changing projection
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);
    glMatrixMode(GL_MODELVIEW); //default 

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

 return 0;
}
