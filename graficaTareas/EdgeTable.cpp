#include "EdgeTable.h"

EdgeTable::EdgeTable()
{

}

void EdgeTable::build(const vector<Point> & points)
{
    int yPrev = points[points.size()-2].y;
    Point v1=points.back();
    for (unsigned int i = 0; i < points.size(); i++){
        Point v2 = points[i];
        if (v1.y != v2.y){
            if (v1.y < v2.y)
                makeEdge (v1,v2,yNext(i,points)); //up edge
            else
                makeEdge(v2,v1,yPrev); // down edge
        }

        yPrev = v1.y;
        v1 = v2;
    }
}

void EdgeTable::makeEdge(Point min, Point max, int yComp)
{
    Edge n;

    n.Xinc = (double)(max.x-min.x)/(max.y-min.y);
    n.XofYMin = min.x;
    if (max.y < yComp)
        n.Ymax = max.y-1;
    else
        n.Ymax = max.y;

    if(!Edges.count(min.y))
        Edges[min.y]={};

    insertEdge (Edges[min.y],n);

}

int EdgeTable::yNext(unsigned int i , vector<Point> points)
{

    unsigned int j=0;
    if (i+1 < points.size())
        j = i+1;

    while (points[i].y == points[j].y)
        if ( j+1 < points.size())
            j++;
        else
            j = 0;

    return points[j].y;
}
