#ifndef GLVIEWER_H
#define GLVIEWER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <vector>
#include <iostream>
#include <fstream>



using namespace std;

const double pi =3.14159265359;

class GLViewer: public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLViewer(QWidget *parent) : QOpenGLWidget(parent) {}
    vector<vector<QPoint>> mPoints;


protected:

    void initializeGL()
    {
        initializeOpenGLFunctions();

        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glViewport(0,0,width(),height());
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-width(), width(), height(), 0,-width(), width());
        glMatrixMode(GL_MODELVIEW);

    }

    void resizeGL(int w, int h)
    {
        // Update projection matrix and other size related settings:
        //m_projection.setToIdentity();
        //m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

    }
    void paintGL()
    {
        cout<<"pinto"<< width()<<" " <<height()<<endl;

        glColor3f(1,1,1);
        //glPointSize(5);
        glBegin(GL_POINTS);




        double thetaDegrees = 30;
        double thetaRadians = thetaDegrees*pi/180;

        //double t=0;
        cout<<mPoints.size()<<endl;
        double t=0;
        std::ofstream out("prueba.xyz");
        for (int i = 0 ; i<mPoints.size();++i){
            for (int j = 0 ; j<mPoints[i].size();++j){

                double angle=t*pi/180;
                double x=(((mPoints[i][j].x()-450/*-(width()/2))*(width()/Wvideo*/)))/sin(thetaRadians);
                double y=mPoints[i][j].y();//*(height()/Hvideo));
                double z=0;
                double xR=(z*sin(angle))+(x*cos(angle));
                double zR=(z*cos(angle))-(x*sin(angle));



                out<<xR<<' '<<y<<' '<<zR<<'\n';
                glVertex3f(xR,y,zR);
            }
            t+=0.7;
        }

        glEnd();

    }

public:
    void setPoints(vector<vector<QPoint>>& points){
        mPoints=points;
        update();
    }

};

#endif // GLVIEWER_H



