/*
    We are launching the Qt Main Window (that will act as the real controller)
    
    It will run and display the Window designed with the GUI Library Qt5.4
    
    At the same time QMainWindow will act as an initial interface of the application
    inside QMainWindow will be contained two sub-types of the interface to show the 

    
    We are hacking the frontend action to execute all our code
    before exiting.

    Init::InitEverything--\
                          |->FrontendAction::ExecuteAction-\
                                                            |-Controller::Loop()
                          /----------------<---------------/
                          |-Exit()
*/


#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"


int main(int argc, const char **argv) {
  //Init::InitEverything(argc,argv);
  //return 0;
  QApplication a(argc, (char **)argv);
  MainWindow w;
  w.show();

  a.exec();
}
