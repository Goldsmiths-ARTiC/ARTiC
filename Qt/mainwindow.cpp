
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
  //We want to have two ways to visualize graphically the AST, and we want to switch between them. We set the openGL invisible first
  ui->treeWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
  delete ui;
}
///This function will be called when a file is selected on the QMainWindow or through the refresh option
///It will check that the file contains the correct extension for reading and will read it.
void MainWindow::importFile(QString importFile){

  QString fileName = importFile;
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

      //Now we have to clear all the views (those who needed)
      ui->myGLWidget->clear_view();
      ui->treeWidget->clear();

      //----- This part should be encapsulated, as it's a process of 'interpreting' the imported model of the AST ------//
      //Reading from the internal Model
      //First we read the code, and draw it in the proper place
      ui->textBrowser->setText(QTVisualizer::get_code()->data());

      //get the number of functions that have been read from the ASTParser
      QString numOfFunctions = QString("Number of functions found: %1").arg(QTVisualizer::get_functions()->size());
      ui->textBrowser->append(numOfFunctions); 

      //Print the tree!
      QTreeWidgetItem* item;
      QTreeWidgetItem* functions_node = new QTreeWidgetItem();
      functions_node->setText(0, "Functions:");
      ui->treeWidget->addTopLevelItem(functions_node);
      int i_param = 0;
      for (int i = 0; i < QTVisualizer::get_functions()->size(); ++i){
        ui->textBrowser->append(QTVisualizer::get_functions()->at(i)->data());
        ui->myGLWidget->push_function(QTVisualizer::get_functions()->at(i));
        item = new QTreeWidgetItem();
        functions_node->addChild(item);
        item->setText(0, QTVisualizer::get_functions()->at(i)->data());
        int num_params = QTVisualizer::get_num_params()->at(i);
        QTreeWidgetItem* new_param;
        for (int j = 0; j < num_params; ++j){
          new_param = new QTreeWidgetItem();
          item->addChild(new_param);
          new_param->setText(0, QString("Param--> %1").arg(QTVisualizer::get_params()->at(i_param + j)->data()));
        }
        i_param += num_params;
      }

      //get the number of variables that have been read from the ASTParser
      QString numOfVariables = QString("\nNumber of variables found: %1 ").arg(QTVisualizer::get_variables()->size());
      ui->textBrowser->append(numOfVariables);
      //for every variable found, print each one
      for (int i = 0; i < QTVisualizer::get_variables()->size(); ++i){
        ui->textBrowser->append(QTVisualizer::get_variables()->at(i)->data());
        ui->myGLWidget->push_variable(QTVisualizer::get_variables()->at(i));
      }

      /*for (int i = 0; i < QTVisualizer::get_params()->size(); ++i){
        ui->textBrowser->append(QTVisualizer::get_params()->at(i)->data());
      }*/
      //----- This part should be encapsulated, as it's a process of 'interpreting' the imported model of the AST ------//
    }
  }
  else{
    //If there was no file, we warn the user to input some file
    ui->textBrowser->setText("Please pick a file!");
  }
}

void MainWindow::on_actionImport_file_triggered()
{
  //Open a dialog to receive a new file to be displayed
  import_fileName = QFileDialog::getOpenFileName(this, "Select the file to be displayed", "", "File (*.c *.h)");
  importFile(import_fileName);
}

void MainWindow::on_actionExport_file_triggered()
{
  ui->textBrowser->setText("Please come back later..this function has not been added yet");
}

void MainWindow::on_actionExit_application_triggered()
{
  QApplication::exit(0); //close the program
}
//Open up our GitHub repository
void MainWindow::on_actionAbout_this_project_triggered()
{
  QDesktopServices::openUrl(QUrl("https://github.com/Goldsmiths-ARTiC/ARTiC", QUrl::TolerantMode));
}
//Open up the LLVM website in the browser
void MainWindow::on_actionAbout_LLVM_and_clang_triggered()
{
  QDesktopServices::openUrl(QUrl("http://llvm.org/", QUrl::TolerantMode));
}
//Change between the two views that we have, an OpenGL window and a TreeView window
void MainWindow::on_actionChange_view_triggered()
{
  //Here we change the visibility of the two visualizers of the right. This going to be edited later on
  //  We would be able to expand this part later on. For now we only offer two views
  //This will ensure that while one is visible, the other cannot be visible. Only one display at a time.
  ui->myGLWidget->setVisible(!ui->myGLWidget->isVisible());
  ui->treeWidget->setVisible(!ui->myGLWidget->isVisible());
}
//Just incase the user has changed the file and would like to check any changes, they can refresh.
void MainWindow::on_actionRefresh_triggered()
{
  importFile(import_fileName);
}
///We want to clear everything
///Clear the filename, textBrowser and the OpenGLWidget
void MainWindow::on_actionClear_triggered()
{
  import_fileName.clear();
  ui->textBrowser->setText("");
  ui->treeWidget->clear();
  ui->myGLWidget->clear_view();
}
