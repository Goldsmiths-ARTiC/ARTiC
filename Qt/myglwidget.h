// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

/// @brief This MyGLWidget is our own widget made with the QGLWidget base.
///   Due to the time of the projects, we've opted to used this interface and
///   this module that will let us draw simple forms and objects in openGL
///   using some of the openGL 1.0 primitives. One easy update (even though
///   might require some time) would be updating this interface to use openGL 2.0
///     The easy way to do this improvement would be to replace this current
///     widget with a widget subclass of an QOpenGLWidget.

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

public slots:

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;
  //With this functions we can control the movement and actions of the mouse
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

public slots:
  // slots for xyz-rotation 
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);

signals:
  // signaling rotation from mouse movement
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);

private:
  void draw_block();
  void draw();

  //Basic information of the rotations of the model
  int xRot;
  int yRot;
  int zRot;
  int zoomFront;

  QPoint lastPos; //To be able to track the movement of the mouse
};

#endif // MYGLWIDGET_H

