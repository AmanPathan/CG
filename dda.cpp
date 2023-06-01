#include <iostream>
#include <GL/glut.h>

using namespace std;
int choice;

void DDA(int x1, int y1, int x2, int y2, int choice)
{
    float length;
    int dx = (x2 - x1);
    int dy = (y2 - y1);

    length = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float x_increment = dx / length;
    float y_increment = dy / length;

    float x = x1;
    float y = y1;

    if (choice == 4)
    {
        glPointSize(3.0); // set pixel size = 3 if choice is 4(solid line)
    }
    else
    {
        glPointSize(1.0); // else set pixel size = 1
    }

    glBegin(GL_POINTS);
    int j = 0;
    for (int i = 0; i <= length; i++)
    {

        if (choice == 1 || choice == 4)
        {
            glVertex2i((int)(x), (int)(y));
        }
        if (j % 20 == 0 && choice == 2)
        {
            glVertex2i((int)(x), (int)(y));
        }
        if (j < 5 && choice == 3)
        {
            glVertex2i((int)(x), (int)(y));
        }

        j = (j + 1) % 10;
        x += x_increment;
        y += y_increment;
    }
    glEnd();
}

void myMouse(int button, int state, int mouseX, int mouseY)
{
    static int newX1, newY1, newX2, newY2, pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINES);

            // Draw x-axis
            glVertex2i(-500, 0);
            glVertex2i(500, 0);
            // Draw y-axis
            glVertex2i(0, -500);
            glVertex2i(0, 500);
            glEnd();
            pt++;
        }
        else
        {
            if (pt == 1)
            {
                int xx1 = -500 + 2 * mouseX;
                int yy1 = 500 - 2 * mouseY;
                newX1 = xx1;
                newY1 = yy1;
                pt++;
            }
            else
            {
                int xx2 = -500 + 2 * mouseX;
                int yy2 = 500 - 2 * mouseY;
                newX2 = xx2;
                newY2 = yy2;
                DDA(newX1, newY1, newX2, newY2, choice);
                pt = 0;
            }
        }
    }
    glFlush();
}
void display()
{
    glFlush();
}

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set clear color to black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0); // Set the coordinate system's range
}

int main(int argc, char **argv)
{
    cout << "Enter choice of line:" << endl;
    cout << "1:Simple Line" << endl;
    cout << "2:Dotted Line" << endl;
    cout << "3:Dashed Line" << endl;
    cout << "4:Solid Line" << endl;
    cin >> choice;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);     // Set the window size
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("DDA Algorithm");
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    init();
    glutMainLoop();
    return 0;
}
