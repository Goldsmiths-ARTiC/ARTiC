// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
  resetView();
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::resetView(){
  xRot = INI_XROT;
  yRot = INI_YROT;
  zRot = INI_ZROT;
  xTrans = INI_XTRANS;
  yTrans = INI_YTRANS;
  zTrans = INI_ZTRANS;
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    //Initializing the openGL canvas
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Seting up the lights
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    //We start to paint, cleaning the canvas
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //We translate and rotate
    glLoadIdentity();
    glTranslatef(xTrans, yTrans, zTrans);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    //And then we draw!
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 45.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

//This will be used to controle the key events and to move the openGl
void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  switch (event->key()){
  case Qt::Key_Up:
  case Qt::Key_8:
    yTrans += 0.5f;
    updateGL();
    break;
  case Qt::Key_Down:
  case Qt::Key_2:
    yTrans -= 0.5f;
    updateGL();
    break;
  case Qt::Key_Left:
  case Qt::Key_4:
    xTrans -= 0.5f;
    updateGL();
    break;
  case Qt::Key_Right:
  case Qt::Key_6:
    xTrans += 0.5f;
    updateGL();
    break;
  case Qt::Key_Plus:
    updateGL();
    break;
  case Qt::Key_Minus:
    updateGL();
    break;
  case Qt::Key_0:
    resetView();
    updateGL();
    break;
  }
  //updateGL();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{
  //We start drawing things
  //We have now to change this to read from the current functions, and set it up as a function to draw functions!
  glPushMatrix();
  for (std::string* func_name : func_list){
    draw_function(func_name);
    glTranslatef(0.0f, -0.5f, 0.0f);
  }
  for (std::string* variable_name : variable_list){
    draw_v(variable_name);
      glTranslatef(0.0f, -0.5f, 0.0f);
    }
  glPopMatrix();
}

//This part of the code is just an 'ongoingwork'. This afternoon it will be replaced by a FunctionBlob class ********//
void MyGLWidget::draw_function(std::string * name){
  draw_block(1.0f);
  glDisable(GL_DEPTH_TEST);
  qglColor(Qt::red);
  renderText(0.5f, 0.0f, 0.0f, name->data());
  glEnable(GL_DEPTH_TEST);
}

//This part of the code is just an 'ongoingwork'. This afternoon it will be replaced by a FunctionBlob class ********//
void MyGLWidget::draw_v(std::string * name){
  draw_variable(0.5f);
  glDisable(GL_DEPTH_TEST);
  qglColor(Qt::white);
  renderText(0.5f, 0.0f, 0.0f, name->data());
  glEnable(GL_DEPTH_TEST);
}

//This function will draw a pyramid!
void MyGLWidget::draw_block(float size){
  float scale_size = size*0.4f;
  float half_size = scale_size*0.5f;
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1 * half_size);
  glVertex3f(-1 * scale_size, -1 * half_size, 0);
  glVertex3f(-1 * scale_size, 1 * half_size, 0);
  glVertex3f(1 * scale_size, 1 * half_size, 0);
  glVertex3f(1 * scale_size, -1 * half_size, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(0, -1, 0.707);
  glVertex3f(-1 * scale_size, -1 * half_size, 0);
  glVertex3f(1 * scale_size, -1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(1, 0, 0.707);
  glVertex3f(1 * scale_size, -1 * half_size, 0);
  glVertex3f(1 * scale_size, 1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(0, 1, 0.707);
  glVertex3f(1 * scale_size, 1 * half_size, 0);
  glVertex3f(-1 * scale_size, 1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(-1, 0, 0.707);
  glVertex3f(-1 * scale_size, 1 * half_size, 0);
  glVertex3f(-1 * scale_size, -1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
}

//This function will draw a pyramid!
void MyGLWidget::draw_variable(float size){
  float scale_size = size*0.4f;
  float half_size = scale_size*0.5f;
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1 * half_size);
  glVertex3f(-1 * scale_size, -1 * half_size, 0);
  glVertex3f(-1 * scale_size, 1 * half_size, 0);
  glVertex3f(1 * scale_size, 1 * half_size, 0);
  glVertex3f(1 * scale_size, -1 * half_size, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(0, -1, 0.707);
  glVertex3f(-1 * scale_size, -1 * half_size, 0);
  glVertex3f(1 * scale_size, -1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(1, 0, 0.707);
  glVertex3f(1 * scale_size, -1 * half_size, 0);
  glVertex3f(1 * scale_size, 1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(0, 1, 0.707);
  glVertex3f(1 * scale_size, 1 * half_size, 0);
  glVertex3f(-1 * scale_size, 1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3f(-1, 0, 0.707);
  glVertex3f(-1 * scale_size, 1 * half_size, 0);
  glVertex3f(-1 * scale_size, -1 * half_size, 0);
  glVertex3f(0, 0, 1.2 * half_size);
  glEnd();
}

//This is to push a new function!
void MyGLWidget::push_function(std::string * name){
  func_list.push_back(name);
}

//This is to push a new variable!
void MyGLWidget::push_variable(std::string * name){
  variable_list.push_back(name);
}

//This will clear all the elements, use with caution!
void MyGLWidget::clear_view(){
  printf("Clearing the gl!");
  func_list.clear();
  printf("--->Size of this %i", func_list.size());
}