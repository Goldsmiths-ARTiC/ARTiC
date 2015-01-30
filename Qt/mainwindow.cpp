
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
  QFileInfo fi = fileName; //get fileinfo as an input string
  QString ext = fi.suffix(); //get the extension of the file. test.c will give ext = c

  if (!fileName.isEmpty()){
    if (ext != "c"){ //if its not a c file, we're not interested at the moment
      ui->textBrowser->setText("Wrong file extension, please try a '.c' file.");
    }
    else{
      //Setting up the three arguments required (name program, name file, two dashes - to avoid using compilation database)
      ui->textBrowser->setText("Loading the file: ");
      ui->textBrowser->append(fileName);
      QByteArray byteArray = fileName.toUtf8();
      const char *cStringFname = byteArray.constData();
      //Imports the file
      const char *arguments[] = { "ARTiC.exe", cStringFname, "--" };
      Init::InitEverything(3, (const char**)arguments, ui->myGLWidget);
      ui->statusBar->setStatusTip(fileName);
    }
  }
  else{
    ui->textBrowser->setText("Please pick a file!");
  }
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
