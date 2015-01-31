#ifndef BLOBS_H
#define BLOBS_H

#include <QtOpenGL>

class Blobs :public Blobs
{
public:
  Blobs()
  {}
  ~Blobs()
  {}

  //******* This part of the code is just an 'ongoingwork'. This afternoon it will be replaced by a FunctionBlob class ********//
  void MyGLWidget::draw_function(std::string * name){
    draw_block(1.0f);
    glDisable(GL_DEPTH_TEST);
    qglColor(Qt::red);
    renderText(0.5f, 0.0f, 0.0f, name->data());
    glEnable(GL_DEPTH_TEST);
  }

  void blob_variable


  //This function will draw a pyramid!
  void blob_function(float size){
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
}

#endif