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
    gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) );

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

Polygon poly;
vector<Point> points;
bool waitInput=true;

void fillPolygon()
{
    glColor3f(1,1,1);
    //gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) );

    // Polygon to fill;
    //Polygon poly({Point(400,30),Point(150,80),Point(80,400),Point(300,200),Point(500,300)});
    //Polygon poly({Point(270,50),Point(350,200),Point(400,50),Point(450,250),Point(375,325),
      //            Point(200,325),Point(100,250),Point(200,50),Point(270,225)});
    if (!poly.points.empty()){
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
    }

    glFlush();
}

void mouse(int bin, int state , int x , int y) {
    if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && waitInput){
        points.push_back(Point(x,glutGet(GLUT_WINDOW_HEIGHT)-y));

        glPointSize(2);
        glColor3f(1,1,1);
        glBegin(GL_POINTS);
        glVertex2i (x,glutGet(GLUT_WINDOW_HEIGHT)-y);
        glEnd();
        glFlush();

    }
}
void scale(Polygon& polyg,float dx, float dy){

    vector<Point> temp;
    for (auto &point:polyg.points)
        temp.push_back(Point(point.x*dx + polyg.center.x*(1-dx) ,point.y*dy + polyg.center.y*(1-dy)));

    polyg.init(temp);
}

void move(Polygon& polyg,float dx, float dy){

    vector<Point> temp;
    for (auto &point:polyg.points)
        temp.push_back(Point(point.x + dx ,point.y+dy));

    polyg.init(temp);
}


void rotate(Polygon& polyg,float angle){
    double pi=3.14159265359;
    vector<Point> temp;
    for (auto &point:polyg.points)
        temp.push_back(Point(point.x*(cos(angle*pi/180))+ point.y*(-sin(angle*pi/180)) + polyg.center.x*(1-cos(angle*pi/180))+polyg.center.y*(sin(angle*pi/180)),
                             point.x*(sin(angle*pi/180))+ point.y*(cos(angle*pi/180)) + polyg.center.y*(1-cos(angle*pi/180))-polyg.center.x*(sin(angle*pi/180))));

    polyg.init(temp);
}

void keyboard(unsigned char Key, int , int )
{
    switch(Key){
        case 13/*enter*/:
            if (waitInput){
                poly.init(points);
                fillPolygon();
                waitInput=false;
            }
            break;
        case 45/*minus*/:
        if(!waitInput){
            scale(poly,0.5,0.5);
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            fillPolygon();
        }
            cout<<"scale -"<<endl;
            break;
        case 43/*add*/:
        if(!waitInput){
            scale(poly,2,2);
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            fillPolygon();
        }
            cout<<"scale +"<<endl;
            break;
        case 'r':
            if(!waitInput){
                rotate(poly,-20);
                glClear(GL_COLOR_BUFFER_BIT);
                glFlush();
                fillPolygon();
            }
            cout<<"rotate rigth"<<endl; break;
        case 'l':
            if(!waitInput){
                rotate(poly,20);
                glClear(GL_COLOR_BUFFER_BIT);
                glFlush();
                fillPolygon();
            }
            cout<<"rotate left"<<endl; break;
        case 'c':
            waitInput=true;
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            points.clear();
            cout<<"clear"<<endl;
            break;
    };
}

void specialKey(int Key, int , int )
{
    switch(Key){
        case GLUT_KEY_LEFT:
            if(!waitInput){
                move(poly,-10,0);
                glClear(GL_COLOR_BUFFER_BIT);
                glFlush();
                fillPolygon();
            }
            cout<<"move left"<<endl; break;
        case GLUT_KEY_RIGHT:
            if(!waitInput){
                move(poly,10,0);
                glClear(GL_COLOR_BUFFER_BIT);
                glFlush();
                fillPolygon();
            }
            cout<<"move right"<<endl; break;
    case GLUT_KEY_UP:
        if(!waitInput){
            move(poly,0,10);
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            fillPolygon();
        }
        cout<<"move up"<<endl; break;
    case GLUT_KEY_DOWN:
        if(!waitInput){
            move(poly,0,-10);
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            fillPolygon();
        }
        cout<<"move down"<<endl; break;
    }

}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB );
    glutInitWindowSize(450, 450);

    glutInitWindowPosition(50, 50);
    glutCreateWindow("Fill");
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    myInit();
    glFlush();


    glutMainLoop();
    return 0;
}
