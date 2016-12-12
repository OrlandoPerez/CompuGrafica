#include "Polygon.h"


Polygon::Polygon(vector<Point> p)
{
    init(p);
}

void Polygon::init(vector<Point> p)
{
    Xmin=0;
    Xmax=0;
    Ymin=0;
    Ymax=0;

    points=p;
    double xcenter,ycenter=0;
    for(Point &i:p){
        xcenter+=i.x;
        ycenter+=i.y;

        if(i.x < Xmin) Xmin=i.x;
        if(i.x > Xmax) Xmax=i.x;
        if(i.y < Ymin) Ymin=i.y;
        if(i.y > Ymax) Ymax=i.y;
    }
    center=Point(xcenter/p.size(),ycenter/p.size());

}

void Polygon::draw()
{
    glBegin(GL_LINE_LOOP);
    for (auto &point:points)
        glVertex2i (point.x,point.y);
    glEnd();
}
