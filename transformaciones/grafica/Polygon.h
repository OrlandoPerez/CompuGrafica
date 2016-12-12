#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
#ifndef POLYGON_H
#define POLYGON_H

class Point{
public:
    Point(){}
    Point(int pointX,int pointY):x(pointX),y(pointY){}
    ~Point(){}
    void inline operator =(const Point& point){x=point.x;y=point.y;}
    int x;
    int y;
};

class Polygon
{
public:
    Polygon(){}
    Polygon(vector<Point> p);
    ~Polygon(){points.clear();}
    void init(vector<Point> p);
    int size(){return points.size();}
    void draw();
    vector<Point> points;
    int Xmax=0;
    int Xmin=0;
    int Ymax=0;
    int Ymin=0;
    Point center;
};


#endif // POLYGON_H


