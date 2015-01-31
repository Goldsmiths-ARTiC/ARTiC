#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <string>


/// @brief This is the main window of the application. This will control the flow of the application since it's opened untill the end
///   This class will actually behave as the 'CONTROLLER' as is the one who will receive the inputs from the user and translate those
///   input into actions. It will call the class inside Init to import and decode an AST with an ASTVisitor made with libtooling
///   It will contain likewise the different ways to show the code, that, potentially, will be different widgets.
///     There will be the possibility to create different widgets and they could be able to receive the inputs from the user
///     to modify the AST. < This feature is not yet implemented, we have focused in 'visualizing' the code in different way >
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
  QString import_fileName;
  void importFile(QString);

private slots:
//This set of slots are those that will be called with the menu bar and other buttons
    void on_actionImport_file_triggered();

    void on_actionExit_application_triggered();

    void on_actionAbout_this_project_triggered();

    void on_actionAbout_LLVM_and_clang_triggered();

    void on_actionChange_view_triggered();

    void on_actionExport_file_triggered();

    void on_actionRefresh_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
