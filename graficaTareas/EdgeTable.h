#include <unordered_map>
#include "Polygon.h"

#ifndef EDGETABLE_H
#define EDGETABLE_H
class Edge
{
public:
    Edge(){}
    int Ymax=-1;
    double XofYMin=0;
    double Xinc=0;
};

class EdgeTable
{
public:
    EdgeTable();
    EdgeTable(const Polygon &poly){build(poly.points);}
    ~EdgeTable(){}
    void build (const vector<Point> &points);
    void makeEdge (Point min, Point max, int yComp);
    int yNext (unsigned int i, vector<Point> points);

    unordered_map<int,vector<Edge> > Edges;
};

#endif // EDGETABLE_H



//*************EDGE TABLE METHODS
inline void insertEdge (vector<Edge>& vect, const Edge& item)
{
    /*vector<Edge>::iterator curr = vect.begin();

    while ((curr != vect.end()) && ((*curr).XofYMin < item.XofYMin))
        curr++;*/
    unsigned int i=0;
    for(;i<vect.size();++i)
        if(vect[i].XofYMin > item.XofYMin)
            break;


    vect.insert(vect.begin()+i,item);
}

