#ifndef VISUALIZER_H_INCLUDED
#define VISUALIZER_H_INCLUDED

class Controller;

class Visualizer
{
public:
    virtual  ~Visualizer() = 0{}


    virtual void OnActive(){}
    virtual void OnInactive(){}

    virtual void SetController(Controller* c){};
    virtual void Update() = 0{}
    virtual void Init() = 0{}
private:
};


#endif