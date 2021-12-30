#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <list>
using namespace std;

class character
{
public:
    char c;
    void *font;
    float r, g, b;

    character(char c, void *font, float r, float g, float b)
    {
        this->c = c;
        this->font = font;
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

std::list<character> my_string;

//global variables
float r = 1.0, g = 1.0, b = 1.0;
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void draw_character(character ch)
{
    // glColor3f(ch.r, ch.g, ch.b);
    glutBitmapCharacter(ch.font, ch.c);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r, g, b);

    glRasterPos2f(0.0, 0.0);
    glLoadIdentity();

    for (auto it = my_string.begin(); it != my_string.end(); ++it)
    {
        draw_character(*it);
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key >= 32 && key <= 127)
    {
        my_string.push_back(character(key, font, r, g, b));
    }
    else if (key == '\b')
    {
        if (!my_string.empty())
        {
            my_string.pop_back();
        }
    }
    else if (key == 27)
    {
        exit(0);
    }

    glutPostRedisplay();
}

void color_menu(int id)
{
    switch (id)
    {
    case 1:
        // make color red
        r = 1.0;
        g = 0.0;
        b = 0.0;

        break;

    case 2:
        // make color green
        r = 0.0;
        g = 1.0;
        b = 0.0;
        break;
    case 3:
        // make color blue
        r = 0.0;
        g = 0.0;
        b = 1.0;
        break;
    case 4:
        // make color Yellow
        r = 1.0;
        g = 1.0;
        b = 0.0;
        break;
    case 5:
        // make color cayan
        r = 0.0;
        g = 1.0;
        b = 1.0;
        break;

    case 6:
        //make color magenta
        r = 1.0;
        g = 0.0;
        b = 1.0;
        break;
    default:
        break;
    }
}

void font_menu(int id)
{
    switch (id)
    {
    case 1:
        font = GLUT_BITMAP_TIMES_ROMAN_10;
        break;
    case 2:
        font = GLUT_BITMAP_TIMES_ROMAN_24;
        break;
    case 3:
        font = GLUT_BITMAP_HELVETICA_10;
        break;
    case 4:
        font = GLUT_BITMAP_HELVETICA_12;
        break;
    case 5:
        font = GLUT_BITMAP_HELVETICA_18;
        break;
    case 6:
        font = GLUT_BITMAP_8_BY_13;
        break;
    case 7:
        font = GLUT_BITMAP_9_BY_15;
        break;
    default:
        break;
    }
}

void main_menu(int id)
{
    switch (id)
    {
    case 1:
        my_string.clear();
        font = GLUT_BITMAP_TIMES_ROMAN_24;
        // reset color
        r = 1.0;
        g = 1.0;
        b = 1.0;
        break;
    case 2:
        exit(0);
        break;
    default:
        break;
    }
}

void create_menu()
{
    int color_menu_id = glutCreateMenu(color_menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Cyan", 5);
    glutAddMenuEntry("Magenta", 6);

    int font_menu_id = glutCreateMenu(font_menu);
    glutAddMenuEntry("Times Roman 10", 1);
    glutAddMenuEntry("Times Roman 24", 2);
    glutAddMenuEntry("Helvetica 10", 3);
    glutAddMenuEntry("Helvetica 12", 4);
    glutAddMenuEntry("Helvetica 18", 5);
    glutAddMenuEntry("8 by 13", 6);
    glutAddMenuEntry("9 by 15", 7);

    int menu_id = glutCreateMenu(main_menu);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Exit", 2);
    glutAddSubMenu("Color", color_menu_id);
    glutAddSubMenu("Font", font_menu_id);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myIdle()
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Notepad");

    init();

    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION); //only switch when changing projection
    glLoadIdentity();
    gluOrtho2D(0, -20, 20, -5);

    glMatrixMode(GL_MODELVIEW); //default

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(myIdle);

    create_menu();

    glutMainLoop();

    return 0;
}
