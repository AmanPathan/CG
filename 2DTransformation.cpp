#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

int pntX1, pntY1,decision = 0, choice = 0, edges = 4;

vector<int> pntX= {1,1,200,200};
vector<int> pntY= {1,200,200,1};

double scalefactorX, scalefactorY;
char reflectionAxis;
double theta;
int transX, transY;
int arbX, arbY;

double round(double d){
    return floor(d+0.5);
}

void drawPolygon(){
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    for(int i =0;i<edges;i++){
        glVertex2i(pntX[i], pntY[i]);
    }
    glEnd();
}

void drawPolygonTrans(int tx, int ty){
    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
    for(int i =0;i<edges;i++){
        glVertex2i(pntX[i]+tx, pntY[i]+ty);
    }
    glEnd();
}

void drawPolygonMirroReflection(char reflectionAxis){
    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
    if(reflectionAxis == 'x' || reflectionAxis == 'X'){
        for(int i =0;i<edges;i++){
            glVertex2i(round(pntX[i]), round(pntY[i]*-1));
        }
    }
    else if(reflectionAxis == 'y' || reflectionAxis == 'Y'){
        for(int i =0;i<edges;i++){
            glVertex2i(round(pntX[i]*-1), round(pntY[i]));
        }
    }
    glEnd();
}

void drawScaledPolygon(double m, double n){
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,1.0);
    for(int i =0;i<edges;i++){
        glVertex2i(round(pntX[i]*m), round(pntY[i]*n));
    }
    glEnd();
}

void drawrotated(int degree,int arbX,int arbY){
    float radian = 3.14 * degree / 180;

    vector<int> newX;
    vector<int> newY;

    float cx = (pntX[0] + pntX[1] + pntX[2] + pntX[3]) / 4.0;
    float cy = (pntY[0] + pntY[1] + pntY[2] + pntY[3]) / 4.0;

    for(int i = 0; i < edges; i++){
        newX.push_back(pntX[i] - cx - arbX );
        newY.push_back(pntY[i] - cy - arbY );
    }

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);

    for(int i = 0; i < edges; i++){
        float m = newX[i] * cos(radian) - newY[i] * sin(radian);
        float n = newX[i] * sin(radian) + newY[i] * cos(radian);
        glVertex2i(round(m + cx + arbX), round(n + cy +arbY));
    }

    glEnd();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    // Draw x-axis
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    // Draw y-axis
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    switch (decision)
    {
    case 1://translation
        drawPolygon();
        drawPolygonTrans(transX,transY);
        break;

    case 2://scaling
        drawPolygon();
        drawScaledPolygon(scalefactorX,scalefactorY);
        break;

    case 3://reflection
        drawPolygon();
        drawPolygonMirroReflection(reflectionAxis);
        break;

    case 4://rotation
        drawPolygon();
        drawrotated(theta,arbX,arbY);
        break;

    }
    glFlush();
}

void init(void){
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

int main(int argc, char **argv)
{
    cout<<"1.Translation"<<endl;
    cout<<"2.Scaling"<<endl;
    cout<<"3.Reflection"<<endl;
    cout<<"4.Rotation"<<endl;
    cin>>decision;

    switch (decision)
    {
    case 1://translation
        cout<<"Enter the translation factors 'Tx' and 'Ty':";
        cin>>transX>>transY;
        break;

    case 2://scaling
        cout<<"Enter the scale factors 'Sx' and 'Sy':";
        cin>>scalefactorX>>scalefactorY;
        break;

    case 3://reflection
        cout<<"Enter the Reflection Axis X or Y:";
        cin>>reflectionAxis;
        break;

    case 4://rotation
        cout<<"Enter the rotation angle in degree:";
        cin>>theta;
        cout<<"To rotate about arbitary points,Enter arbitary co-ordinates:";
        cin>>arbX>>arbY;
        break;

    default:
        cout<<"Invalid Choice"<<endl;
        break;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformation");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
