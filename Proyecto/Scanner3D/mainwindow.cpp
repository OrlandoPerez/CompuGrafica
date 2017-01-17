#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>

#include <QMessageBox>
#include <QFileDialog>


#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


//#define CGAL_EIGEN3_ENABLED


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/pca_estimate_normals.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/property_map.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/IO/write_xyz_points.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/hierarchy_simplify_point_set.h>

#include <utility> // defines std::pair
#include <list>

const double pi =3.14159265359;


using namespace cv;
using namespace std;




typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

// Point with normal vector stored in a std::pair.
typedef std::pair<Kernel::Point_3, Kernel::Vector_3> PointVectorPair;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPlayer = new Capture();
    connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updateUIVideo(QImage)));

    connect(myPlayer, SIGNAL(finished()),this, SLOT(getPoints()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete myPlayer;
}

void MainWindow::updateUIVideo(QImage img)
{
    if (!img.isNull())
    {
        ui->mVideo->setAlignment(Qt::AlignCenter);
        ui->mVideo->setPixmap(QPixmap::fromImage(img).scaled(ui->mVideo->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }



}




void MainWindow::getPoints()
{
    double thetaDegrees = 30;
    double centerLine = 450;
    double thetaRadians = thetaDegrees*pi/180;

    double t=0;
    ofstream out("output.xyz");
    for (unsigned int i = 0 ; i<myPlayer->mPoints.size();++i){
        for (unsigned int j = 0 ; j<myPlayer->mPoints[i].size();++j){

            double angle=t*pi/180;
            double x=(((myPlayer->mPoints[i][j].x()-centerLine/*-(width()/2))*(width()/Wvideo*/)))/sin(thetaRadians);
            double y=myPlayer->mPoints[i][j].y();//*(height()/Hvideo));
            double z=0;

            double xR=(z*sin(angle))+(x*cos(angle));
            double zR=(z*cos(angle))-(x*sin(angle));


            out<<xR<<' '<<y<<' '<<zR<<'\n';
        }
        t+=0.7;
    }
    out.close();




    QMessageBox::information(this,"Info","Point Cloud Computed Successfully");



}


void MainWindow::on_buttonRun_clicked()
{

    if (!myPlayer->isRunning()){
        myPlayer->Play();
    }



}


void MainWindow::on_buttonFilter_clicked(bool checked)
{
    myPlayer->filterMode = checked;
}

void MainWindow::on_buttonNormal_clicked()
{
    std::list<PointVectorPair> points;
    std::ifstream stream("outputSimplify.xyz");
    if (!stream || !CGAL::read_xyz_points(stream,
                                   std::back_inserter(points),
                                   CGAL::First_of_pair_property_map<PointVectorPair>()))
    {
        cout << "Error: cannot read file "<< endl;
        return;
    }
    stream.close();

    const int nb_neighbors = 18; // K-nearest neighbors = 3 rings
    CGAL::pca_estimate_normals(points.begin(), points.end(),
                                                CGAL::First_of_pair_property_map<PointVectorPair>(),
                                                CGAL::Second_of_pair_property_map<PointVectorPair>(),
                                                nb_neighbors);

    std::list<PointVectorPair>::iterator unoriented_points_begin =
            CGAL::mst_orient_normals(points.begin(), points.end(),
                                     CGAL::First_of_pair_property_map<PointVectorPair>(),
                                     CGAL::Second_of_pair_property_map<PointVectorPair>(),
                                     nb_neighbors);

    // Optional: delete points with an unoriented normal
    // if you plan to call a reconstruction algorithm that expects oriented normals.
    points.erase(unoriented_points_begin, points.end());

    ofstream out1("outputNormal.xyz");

    CGAL::write_xyz_points_and_normals(out1,points.begin(),points.end(),CGAL::First_of_pair_property_map<PointVectorPair>(),CGAL::Second_of_pair_property_map<PointVectorPair>());
    out1.close();

    QMessageBox::information(this,"Info","Normal Computed Succesfully");

}

void MainWindow::on_buttonOpen_clicked()
{
    QString file=QFileDialog::getOpenFileName(this,"Open File","/","Archivo de video (*.mp4)");

    if (!file.isEmpty()){
        if (!myPlayer->loadVideo(file.toStdString()))
            QMessageBox::information(this,"Info","Load File Error");

        ui->mVideo->clear();
    }

}

void MainWindow::on_buttonSimplify_clicked()
{
    std::vector<Kernel::Point_3> points;
    std::ifstream stream("output.xyz");
    if (!stream || !CGAL::read_xyz_points(stream,
                                   std::back_inserter(points)))
    {
        cout << "Error: cannot read file "<< endl;
        return;
    }
    stream.close();


   /* double cell_size = 1.5;
    points.erase(CGAL::grid_simplify_point_set(points.begin(), points.end(), cell_size),
                   points.end());

    std::vector<Kernel::Point_3>(points).swap(points);
*/

    points.erase (CGAL::hierarchy_simplify_point_set (points.begin (), points.end (),
                                                      100, // Max cluster size
                                                      0.01), // Max surface variation
                  points.end ());


    ofstream out("outputSimplify.xyz");

    CGAL::write_xyz_points(out,points.begin(),points.end());
    out.close();

    QMessageBox::information(this,"Info","Points Simplified Successfully");


}
