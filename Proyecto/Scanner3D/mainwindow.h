#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Capture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:

private slots:
    void updateUIVideo(QImage img);
    void getPoints();

    void on_buttonRun_clicked();

    void on_buttonFilter_clicked(bool checked);

    void on_buttonNormal_clicked();

    void on_buttonOpen_clicked();

    void on_buttonSimplify_clicked();

private:
    Ui::MainWindow *ui;

    Capture* myPlayer;
    vector<vector<QPoint>> mPoints;

};

#endif // MAINWINDOW_H
