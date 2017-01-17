/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonOpen;
    QPushButton *buttonRun;
    QPushButton *buttonFilter;
    QPushButton *buttonSimplify;
    QPushButton *buttonNormal;
    QSpacerItem *horizontalSpacer;
    QLabel *mVideo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(631, 444);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonOpen = new QPushButton(centralWidget);
        buttonOpen->setObjectName(QStringLiteral("buttonOpen"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonOpen->sizePolicy().hasHeightForWidth());
        buttonOpen->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(buttonOpen);

        buttonRun = new QPushButton(centralWidget);
        buttonRun->setObjectName(QStringLiteral("buttonRun"));
        sizePolicy.setHeightForWidth(buttonRun->sizePolicy().hasHeightForWidth());
        buttonRun->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(buttonRun);

        buttonFilter = new QPushButton(centralWidget);
        buttonFilter->setObjectName(QStringLiteral("buttonFilter"));
        sizePolicy.setHeightForWidth(buttonFilter->sizePolicy().hasHeightForWidth());
        buttonFilter->setSizePolicy(sizePolicy);
        buttonFilter->setCheckable(true);

        verticalLayout->addWidget(buttonFilter);

        buttonSimplify = new QPushButton(centralWidget);
        buttonSimplify->setObjectName(QStringLiteral("buttonSimplify"));
        sizePolicy.setHeightForWidth(buttonSimplify->sizePolicy().hasHeightForWidth());
        buttonSimplify->setSizePolicy(sizePolicy);
        buttonSimplify->setCheckable(false);

        verticalLayout->addWidget(buttonSimplify);

        buttonNormal = new QPushButton(centralWidget);
        buttonNormal->setObjectName(QStringLiteral("buttonNormal"));
        sizePolicy.setHeightForWidth(buttonNormal->sizePolicy().hasHeightForWidth());
        buttonNormal->setSizePolicy(sizePolicy);
        buttonNormal->setCheckable(false);

        verticalLayout->addWidget(buttonNormal);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        mVideo = new QLabel(centralWidget);
        mVideo->setObjectName(QStringLiteral("mVideo"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mVideo->sizePolicy().hasHeightForWidth());
        mVideo->setSizePolicy(sizePolicy1);
        mVideo->setMinimumSize(QSize(400, 300));
        mVideo->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(mVideo);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 631, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        buttonOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        buttonRun->setText(QApplication::translate("MainWindow", "Scan", 0));
        buttonFilter->setText(QApplication::translate("MainWindow", "View Filter", 0));
        buttonSimplify->setText(QApplication::translate("MainWindow", "Simplify Points", 0));
        buttonNormal->setText(QApplication::translate("MainWindow", "Compute Normal", 0));
        mVideo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
