#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionImport_file_triggered();

    void on_actionExit_application_triggered();

    void on_actionAbout_this_project_triggered();

    void on_actionAbout_LLVM_and_clang_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
