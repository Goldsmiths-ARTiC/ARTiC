
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
  //Open a dialog to receive a new file to be displayed
  QString fileName = QFileDialog::getOpenFileName(this, "Select the file to be displayed", "", "File (*.c *.h)");
  QFileInfo fi = fileName; //get fileinfo as an input string
  QString ext = fi.suffix(); //get the extension of the file. test.c will give ext = c

  //We check that the file it's not empty!
  if (!fileName.isEmpty()){
    if (ext != "c" && ext != "h"){ //if its not a c file, we're not interested at the moment
      ui->textBrowser->setText("Wrong file extension, please try a '.c' or a '.h' file.");
    }
    else{
      //Setting up the three arguments required (name program, name file, two dashes - to avoid using compilation database)
      ui->textBrowser->setText("Loading the file: ");
      ui->textBrowser->append(fileName);
      QByteArray byteArray = fileName.toUtf8();
      const char *cStringFname = byteArray.constData();

      //Imports the file to the model (this needs three parameters). 
      const char *arguments[] = { "ARTiC.exe", cStringFname, "--" }; //The first is irrelelvant, the second is the name of the file and the third has to be -- to avoid looking for the pdb)
      Init::InitEverything(3, (const char**)arguments);
      ui->statusBar->setStatusTip(fileName);

      //----- This part should be encapsulated, as it's a process of 'interpreting' the imported model of the AST ------//
      //Reading from the internal Model
        //First we read the code, and draw it in the proper place
      ui->textBrowser->setText(QTVisualizer::get_code()->data());


      //QString QFuncs = QString::fromStdString(QTVisualizer::get_functions()->data());
      //ui->textBrowser->append(QFuncs);
        //Here will start the process of reading the functions, and sending them to the openGL_VIEW
        
              /* WORK IN PROGRESS! */
      //----- This part should be encapsulated, as it's a process of 'interpreting' the imported model of the AST ------//
    }
  }
  else{
    //If there was no file, we warn the user to input some file
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
