// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

#include "blobs.h"
/// @brief This MyGLWidget is our own widget made with the QGLWidget base.
///   Due to the time of the projects, we've opted to used this interface and
///   this module that will let us draw simple forms and objects in openGL
///   using some of the openGL 1.0 primitives. One easy update (even though
///   might require some time) would be updating this interface to use openGL 2.0
///     The easy way to do this improvement would be to replace this current
///     widget with a widget subclass of an QOpenGLWidget.

class MyGLWidget : public QGLWidget
{

  enum {INI_XROT = 0, INI_YROT = 0, INI_ZROT = 0, INI_XTRANS = 0, INI_YTRANS = 0, INI_ZTRANS = -10};
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

    void clear_view();
    void push_function(std::string * name);
    void push_variable(std::string *name);
    ~MyGLWidget();
signals:

public slots:

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;
  //With this functions we can control the movement and actions of the mouse and the keyboard
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

public slots:
  // slots for xyz-rotation 
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);
  void resetView();

signals:
  // signaling rotation from mouse movement
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);

private:
  void draw_block(float size = 2.0f);
  void draw_variable(float size = 0.5f);
  void draw_function(std::string * name);
  void draw_v(std::string * name);
  void draw();

  //Basic information of the rotations of the model
  int xRot;
  int yRot;
  int zRot;
  float xTrans;
  float yTrans;
  float zTrans;

  QPoint lastPos; //To be able to track the movement of the mouse

  //Basic information of the code 
  std::vector<std::string*> func_list;

  std::vector<FunctionBlob*> blobs;

  std::vector<std::string*> variable_list;
};

#endif // MYGLWIDGET_H

