#include "Polygon.h"


Polygon::Polygon(vector<Point> p):points(p)
{
    for(Point &i:p){
        if(i.x < Xmin) Xmin=i.x;
        if(i.x > Xmax) Xmax=i.x;
        if(i.y < Ymin) Ymin=i.y;
        if(i.y > Ymax) Ymax=i.y;
    }

}

void Polygon::draw()
{
    glBegin(GL_LINE_LOOP);
    for (auto &point:points)
        glVertex2i (point.x,point.y);
    glEnd();
}
