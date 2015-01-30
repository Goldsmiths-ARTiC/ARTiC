#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "init.h"

#include "myglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImport_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select the file to be analyzed", "", "(File (*.*)");

    //Setting up the three arguments required (name program, name file, two dashes - to avoid using compilation database)
    //Setting up the three arguments required (name program, name file, two dashes - to avoid using compilation database)
    char** arguments = new char*[3];
    arguments[0] = new char[5];
    arguments[1] = new char[7];
    arguments[2] = new char[3];
    arguments[0][0] = 'a';
    arguments[0][1] = 'a';
    arguments[0][2] = 'b';
    arguments[0][3] = 'b';
    arguments[0][4] = '\0';
    arguments[1][0] = 't';
    arguments[1][1] = 'e';
    arguments[1][2] = 's';
    arguments[1][3] = 't';
    arguments[1][4] = '.';
    arguments[1][5] = 'c';
    arguments[1][6] = '\0';
    arguments[2][0] = '-';
    arguments[2][1] = '-';
    arguments[2][2] = '\0';

    //InitEverything(3, (const char**)arguments);
}

void MainWindow::on_actionExit_application_triggered()
{
    QApplication::exit(0);
}

void MainWindow::on_actionAbout_this_project_triggered()
{

}

void MainWindow::on_actionAbout_LLVM_and_clang_triggered()
{

}
