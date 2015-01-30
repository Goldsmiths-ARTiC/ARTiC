
#include "init.h"
#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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


    ui->textBrowser->setText("Loading the file: ");
    ui->textBrowser->append(fileName);
    //Imports the file
   // Init::InitEverything(3, (const char**)arguments);
    ui->statusBar->setStatusTip(fileName);
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
