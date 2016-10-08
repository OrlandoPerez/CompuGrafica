#include <iostream>
#include <cmath>
#include <EdgeTable.h>
#include <iostream>
#include <map>

using namespace std;

void myInit()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void regular()
{
    glColor3f(1,1,1);
    glOrtho(-1, 1, -1, 1, -1, 1);

    //numero de lados
    double num=7;

    glBegin(GL_LINE_LOOP);
    for (double i =0; i<= 360;i+= 360/num){

        double angulo = i*3.14159f/180.0f;
        glVertex2f(cos(angulo), sin(angulo));
    }
    glEnd();
    glFlush();
}

void line()
{
    glColor3f(1,1,1);
    gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) );


    // m>1 ,  no horizontal or vertical lines
    Point p1(100,100);
    Point p2(300,300);

    int dx= p2.x-p1.x;
    int dy= p2.y-p1.y;

    int d = 2 * dy-dx;

    int incE =2 *dy;

    int incNE =2 *(dy-dx);

    int x=p1.x;

    int y=p1.y;

    glBegin(GL_POINTS);
    glVertex2i(x,y);

    while (x<p2.x){
        if (d>0){
            d+=incNE;
            ++y;
        }
        else
            d+=incE;

        ++x;

        glVertex2i(x,y);
    }

    glEnd();
    glFlush();
}


// fill

void fillCurrentScan (vector<Edge> actEdges,int currentY)
{
    glBegin(GL_LINES);
    for(unsigned int i=0;i+1<actEdges.size();i+=2){
        glVertex2i((int)actEdges[i].XofYMin , currentY);
        glVertex2i((int)actEdges[i+1].XofYMin ,currentY);
    }
    glEnd();
}
void updateAEL (vector<Edge>& actEdges,int currentY)
{
    vector<Edge> temp;

    for (Edge &Edge:actEdges )
        if (currentY < Edge.Ymax){
            Edge.XofYMin += Edge.Xinc;
            insertEdge (temp,Edge);
        }

    actEdges.clear();
    actEdges = temp;

}

void fillPolygon()
{
    glColor3f(1,1,1);
    gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) );

    // Polygon to fill;
    //Polygon poly({Point(400,30),Point(150,80),Point(80,400),Point(300,200),Point(500,300)});
    Polygon poly({Point(270,50),Point(350,200),Point(400,50),Point(450,250),Point(375,325),
                  Point(200,325),Point(100,250),Point(200,50),Point(270,225)});

    poly.draw();

    EdgeTable ET(poly);
    vector<Edge> AET;

    for (int scanLine = poly.Ymin; scanLine <= poly.Ymax; ++scanLine){
        if(ET.Edges.count(scanLine)){
            for (auto &edge:ET.Edges[scanLine])
                insertEdge (AET,edge);
        }
        if (!AET.empty()){
            fillCurrentScan(AET,scanLine);
            updateAEL (AET,scanLine);
        }
    }

    glFlush();
}

/////////////////////////////////////////////////////////////

void circle()
{
    glColor3f(1,1,1);
    gluOrtho2D( -500, 500.0,-500, 500.0 );

    //radio input
    int r=100;
    int x=0;
    int y=r;

    int d = 1-r;
    int dE =3;
    int dSE =-2*r+5;


    glBegin(GL_POINTS);

    glVertex2i(x,y);glVertex2i(x,-y);glVertex2i(-x,y);glVertex2i(-x,-y);
    glVertex2i(y,x);glVertex2i(y,-x);glVertex2i(-y,x);glVertex2i(-y,-x);

    while (y>x){
        if (d<0){
            d+=dE;
            dE+=2;
            dSE+=2;
        }
        else{
            d+=dSE;
            dE+=2;
            dSE+=4;
            --y;
        }
        ++x;

        glVertex2i(x,y);glVertex2i(x,-y);glVertex2i(-x,y);glVertex2i(-x,-y);
        glVertex2i(y,x);glVertex2i(y,-x);glVertex2i(-y,x);glVertex2i(-y,-x);
    }

    glEnd();
    glFlush();
}

void ellipse()
{
    glColor3f(1,1,1);
    gluOrtho2D( -500, 500.0,-500, 500.0 );

    //radios input
    int rx=150;
    int ry=200;
    int x=0;
    int y=ry;

    double d1 =ry*ry -rx*rx*ry+(rx*rx)/4.0;
    double d2 =ry*ry *(x+0.5)*(x+0.5)+(rx*rx)*(y-1)*(y-1)-(rx*rx*ry*ry);


    glBegin(GL_POINTS);

    glVertex2i(x,y);glVertex2i(x,-y);glVertex2i(-x,y);glVertex2i(-x,-y);

    while (rx*rx* (y-0.5)>ry*ry*(x+1)){
        if (d1<0)
            d1+=ry*ry*(2*x+3);
        else{
            d1+=ry*ry*(2*x+3)+(rx*rx)*(-2*y+2);
            --y;
        }
        ++x;

        glVertex2i(x,y);glVertex2i(x,-y);glVertex2i(-x,y);glVertex2i(-x,-y);
    }

    while (y>0){
        if (d2<0){
            d2+=ry*ry*(2*x+2)+rx*rx*(-2*y+3);
            ++x;
        }
        else
            d2+=rx*rx*(-2*y+3);

        --y;

        glVertex2i(x,y);glVertex2i(x,-y);glVertex2i(-x,y);glVertex2i(-x,-y);
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB );
    glutInitWindowSize(450, 450);

    glutInitWindowPosition(0, 50);
    glutCreateWindow("Regular");
    myInit();
    glutDisplayFunc(regular);

    glutInitWindowPosition(450, 50);
    glutCreateWindow("Line");
    myInit();
    glutDisplayFunc(line);

    glutInitWindowPosition(900, 50);
    glutCreateWindow("Fill");
    myInit();
    glutDisplayFunc(fillPolygon);


    glutInitWindowSize(350, 350);
    glutInitWindowPosition(200, 400);
    glutCreateWindow("Circle");
    myInit();
    glutDisplayFunc(circle);

    glutInitWindowSize(350, 350);
    glutInitWindowPosition(700, 400);
    glutCreateWindow("Ellipse");
    myInit();
    glutDisplayFunc(ellipse);

    glutMainLoop();
    return 0;
}
