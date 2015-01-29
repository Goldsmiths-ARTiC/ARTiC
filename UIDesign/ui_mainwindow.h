/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImport_code;
    QAction *actionExport_image;
    QAction *actionClose;
    QAction *actionCode;
    QAction *actionDiagram;
    QAction *action3D_Blobs;
    QAction *actionAbout_us;
    QAction *actionOur_repository;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *OpenGLLayout;
    QOpenGLWidget *openGLWidget;
    QVBoxLayout *TextLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuVIew;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1150, 570);
        actionImport_code = new QAction(MainWindow);
        actionImport_code->setObjectName(QStringLiteral("actionImport_code"));
        actionExport_image = new QAction(MainWindow);
        actionExport_image->setObjectName(QStringLiteral("actionExport_image"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionCode = new QAction(MainWindow);
        actionCode->setObjectName(QStringLiteral("actionCode"));
        actionDiagram = new QAction(MainWindow);
        actionDiagram->setObjectName(QStringLiteral("actionDiagram"));
        action3D_Blobs = new QAction(MainWindow);
        action3D_Blobs->setObjectName(QStringLiteral("action3D_Blobs"));
        actionAbout_us = new QAction(MainWindow);
        actionAbout_us->setObjectName(QStringLiteral("actionAbout_us"));
        actionOur_repository = new QAction(MainWindow);
        actionOur_repository->setObjectName(QStringLiteral("actionOur_repository"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 1121, 511));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        OpenGLLayout = new QVBoxLayout();
        OpenGLLayout->setSpacing(6);
        OpenGLLayout->setObjectName(QStringLiteral("OpenGLLayout"));
        openGLWidget = new QOpenGLWidget(gridLayoutWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        OpenGLLayout->addWidget(openGLWidget);


        gridLayout->addLayout(OpenGLLayout, 0, 2, 1, 1);

        TextLayout = new QVBoxLayout();
        TextLayout->setSpacing(6);
        TextLayout->setObjectName(QStringLiteral("TextLayout"));
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        TextLayout->addWidget(label);


        gridLayout->addLayout(TextLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1150, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuVIew = new QMenu(menuBar);
        menuVIew->setObjectName(QStringLiteral("menuVIew"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuVIew->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionImport_code);
        menuFile->addAction(actionExport_image);
        menuFile->addAction(actionClose);
        menuVIew->addAction(actionCode);
        menuVIew->addAction(actionDiagram);
        menuVIew->addAction(action3D_Blobs);
        menuHelp->addAction(actionAbout_us);
        menuHelp->addAction(actionOur_repository);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionImport_code->setText(QApplication::translate("MainWindow", "Import (code)", 0));
        actionExport_image->setText(QApplication::translate("MainWindow", "Export (image)", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionCode->setText(QApplication::translate("MainWindow", "Code", 0));
        actionDiagram->setText(QApplication::translate("MainWindow", "Diagram", 0));
        action3D_Blobs->setText(QApplication::translate("MainWindow", "3D Blobs", 0));
        actionAbout_us->setText(QApplication::translate("MainWindow", "About us...", 0));
        actionOur_repository->setText(QApplication::translate("MainWindow", "Our repository", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuVIew->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
