///This file will contain a preliminary version of the blobs classes to be drawn in openGL
/// This is only a visualizer temporal storage, that will contain only the needed information to be drawn by the visualizer
#ifndef BLOBS_INCLUDED_H
#define BLOBS_INCLUDED_H

///This class will be an abstract class that will be used to go through all the blocks and draw them one by one

class Blob {
protected:
  float x;
  float y;
  float z;
  float size;
  bool hover_words;
  bool detail;
  std::string* name;

public:
  Blob() : x(0), y(0), z(0), size(0), hover_words(true), name(nullptr), detail(false) { }

  ~Blob();

  void Draw(QGLWidget* openGL_space) {
    glPushMatrix();
    glTranslatef(x, y, z);
    //This will draw the function name and the block
    openGL_space->qglColor(Qt::green);
    DrawBlock(openGL_space);
    glPopMatrix();
  }

  void DrawBlock(QGLWidget* openGL_space){
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
    //Draw the tag
    if (hover_words)
      glDisable(GL_DEPTH_TEST);
    if (name!=nullptr)
      openGL_space->renderText(half_size, 0.0f, 0.0f, name->data());
    if (hover_words)
      glEnable(GL_DEPTH_TEST);
  }

  void SetName(std::string* n_name){
    name = n_name;
  }

  void SetPos(float n_x, float n_y, float n_z){
    x = n_x;
    y = n_y;
    z = n_z;
  }

  void SwitchHoverWords(){
    hover_words = !hover_words;
  }

  bool HasDetail(){
    return detail;
  }
};


///This is the function blob, it inherits information from the blob to be drawn
class VariableBlob : public Blob{

public:
  VariableBlob(){
    size = 0.75f;
  }

};


///This is the function blob, it inherits information from the blob to be drawn
class ParamBlob : public Blob{

public:
  ParamBlob(){
    size = 0.5f;
  }

  void Draw(QGLWidget* openGL_space) {
    glPushMatrix();
    glTranslatef(x, y, z);
    //This will draw the function name and the block
    openGL_space->qglColor(Qt::blue);
    DrawBlock(openGL_space);
    glPopMatrix();
  }
};

///This is the function blob, it inherits information from the blob to be drawn
class FunctionBlob : public Blob{
  std::string* return_type;
  int level_detail;
  std::vector<ParamBlob*> parameters;

public:
  FunctionBlob(){
    level_detail = 0;
    detail = true;
    size = 1.0f;
  }

  void ChangeLevelDetail(int inc){
    level_detail += inc;
    level_detail = level_detail <= 0 ? 0 : level_detail >= 1 ? 1 : level_detail;
  }

  void Draw(QGLWidget* openGL_space){
    glPushMatrix();
    glTranslatef(x, y, z);
    //This will draw the function name and the block
    openGL_space->qglColor(Qt::red);
    DrawBlock(openGL_space);
    //Now we check the level of detail to draw more things
    //Here we will draw parameters (right), return type (left)
    if (level_detail >= 1){ //Draw as well the parameters
      for (ParamBlob* param : parameters)
        param->Draw(openGL_space);
    }
    if (level_detail >= 2){ //Draw as well the return type
      //TODO
    }
    glPopMatrix();
  }

  void AddParameter(ParamBlob* new_param){
    parameters.push_back(new_param);
  }

  int NumParameters(){
    return parameters.size();
  }
};

#endif