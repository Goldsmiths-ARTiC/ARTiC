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
    for (FunctionBlob * blob : functionBlobs){
      blob->ChangeLevelDetail(1);
    }
    updateGL();
    break;
  case Qt::Key_Minus:
    for (FunctionBlob * blob : functionBlobs){
      blob->ChangeLevelDetail(-1);
    }
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
  for (FunctionBlob * blob : functionBlobs){
    blob->Draw(this);
  }
  for (VariableBlob * blob : variableBlobs){
    blob->Draw(this);
  }
  glPopMatrix();
}

//This is to push a new function!
void MyGLWidget::push_function(std::string * name){
  func_list.push_back(name);

  FunctionBlob* new_blob = new FunctionBlob();
  new_blob->SetName(name);
  new_blob->SetPos(0.0f, 1.0f - functionBlobs.size()*0.5f, 0.0f);
  functionBlobs.push_back(new_blob);
}

//This is to push params to the previous function
//This will work until we send push_params without params
void MyGLWidget::push_params(std::string * name){
  ParamBlob* new_param = new ParamBlob();
  new_param->SetName(name);
  new_param->SetPos(0.75f + functionBlobs.back()->NumParameters()*0.75f, 0.0f, 0.0f);
  functionBlobs.back()->AddParameter(new_param);
}

//This is to push a new variable!
void MyGLWidget::push_variable(std::string * name){
  func_list.push_back(name);

  VariableBlob* new_blob = new VariableBlob();
  new_blob->SetName(name);
  new_blob->SetPos(0.0f, 1.0f - functionBlobs.size()*0.5f - variableBlobs.size()*0.5f, 0.0f);
  variableBlobs.push_back(new_blob);
}

//This will clear all the elements, use with caution!
void MyGLWidget::clear_view(){
  functionBlobs.clear();
  variableBlobs.clear();
}
