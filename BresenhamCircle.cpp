#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

int R;
void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    glVertex2d(x, y);
    glEnd();
}
void bresenhams_circle(int r)
{

    int x = 0;
    int y = r;
    float d = 3 - 2 * r;

    plot(x, y);
    while (x <= y)
    {
        x++;
        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        plot(x, y);
        plot(x, -y);
        plot(-x, y);
        plot(-x, -y);
        plot(y, x);
        plot(-y, x);
        plot(y, -x);
        plot(-y, -x);
    }
}

void display(void)
{
    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    // Draw x-axis
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    // Draw y-axis
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
    bresenhams_circle(R);
    glFlush();
}

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(2.0f);
    gluOrtho2D(-500, 500, -500, 500);
}
int main(int argc, char **argv)
{
    cout << "Enter Value Of R: ";
    cin >> R;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);        
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" bresenhams circle drawing algorithm");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}
