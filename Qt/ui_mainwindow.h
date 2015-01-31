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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "myglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImport_file;
    QAction *actionExport_file;
    QAction *actionExit_application;
    QAction *actionAbout_this_project;
    QAction *actionAbout_LLVM_and_clang;
    QAction *actionChange_view;
    QWidget *centralWidget;
    MyGLWidget *myGLWidget;
    QTextBrowser *textBrowser;
    QTreeView *treeView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1001, 630);
        actionImport_file = new QAction(MainWindow);
        actionImport_file->setObjectName(QStringLiteral("actionImport_file"));
        actionExport_file = new QAction(MainWindow);
        actionExport_file->setObjectName(QStringLiteral("actionExport_file"));
        actionExit_application = new QAction(MainWindow);
        actionExit_application->setObjectName(QStringLiteral("actionExit_application"));
        actionAbout_this_project = new QAction(MainWindow);
        actionAbout_this_project->setObjectName(QStringLiteral("actionAbout_this_project"));
        actionAbout_LLVM_and_clang = new QAction(MainWindow);
        actionAbout_LLVM_and_clang->setObjectName(QStringLiteral("actionAbout_LLVM_and_clang"));
        actionChange_view = new QAction(MainWindow);
        actionChange_view->setObjectName(QStringLiteral("actionChange_view"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        myGLWidget = new MyGLWidget(centralWidget);
        myGLWidget->setObjectName(QStringLiteral("myGLWidget"));
        myGLWidget->setEnabled(true);
        myGLWidget->setGeometry(QRect(570, 30, 401, 491));
        myGLWidget->setMinimumSize(QSize(400, 200));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(30, 30, 521, 491));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(570, 30, 401, 491));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1001, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuHelp->setAcceptDrops(true);
        menuHelp->setToolTipDuration(2);
        menuHelp->setToolTipsVisible(true);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionImport_file);
        menuFile->addAction(actionExport_file);
        menuFile->addAction(actionExit_application);
        menuView->addAction(actionChange_view);
        menuHelp->addAction(actionAbout_this_project);
        menuHelp->addAction(actionAbout_LLVM_and_clang);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QApplication::translate("MainWindow", "Open a file to see ARTiC in action...", 0));
#endif // QT_NO_STATUSTIP
        actionImport_file->setText(QApplication::translate("MainWindow", "Import (file)", 0));
        actionExport_file->setText(QApplication::translate("MainWindow", "Export (file)", 0));
        actionExit_application->setText(QApplication::translate("MainWindow", "Exit application", 0));
        actionAbout_this_project->setText(QApplication::translate("MainWindow", "About us", 0));
        actionAbout_LLVM_and_clang->setText(QApplication::translate("MainWindow", "About LLVM and clang", 0));
        actionChange_view->setText(QApplication::translate("MainWindow", "Change view", 0));
#ifndef QT_NO_STATUSTIP
        myGLWidget->setStatusTip(QApplication::translate("MainWindow", "Open a file to see ARTiC in action...", 0));
#endif // QT_NO_STATUSTIP
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
#ifndef QT_NO_TOOLTIP
        menuHelp->setToolTip(QApplication::translate("MainWindow", "Want to help us?", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        menuHelp->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help...", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
