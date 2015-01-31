#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <map>
#include <cstdio>
#include <functional>

#include "Visualizer.h"
#include "TypeEnum.h"

class Controller
{
public:
    typedef std::function<void(void*)> VisualFunc;
public:
    Controller():shouldExit_(false){}

    Controller(const Controller&) = delete;
    const Controller& operator = (const Controller&) = delete;


    //The main loop, called with the AST tree in context
    void Loop(void)
    {
        v->Init();
        while (!shouldExit_)
        {
            v->Update();
        }
    }

    void Exit()
    {
      shouldExit_ = true;
    }

    void SetVisualizer(Visualizer* vArg)
    {
        if (v != vArg)
        {
            if(v)
            {
              v->Init();
              v->OnInactive();
            }
            v = vArg;
            v->SetController(this);
            v->OnActive();
        }
    }
    //Add a function to the function map, callable by the name given
    bool AddFunction(VisualFunc& func, TypeEnum type)
    {
        functionMap_[type] = func;


        //this is so this function can be called staically
        // for example using a global variable you may do...
        // static const bool call=AddFunction(stuff,stuff)
        // to execute the function before main
        return true;
    }

    //Call a function in the function map, given the name and a pointer for the argument
    void CallFunc(TypeEnum type, void * info)
    {
        if (functionMap_.find(type)!=functionMap_.end())
        {
            //calling a function in the map with data map
            functionMap_.at(type)(info);
        }
    }

    
private:
    Visualizer* v;
    bool shouldExit_;
    std::map<TypeEnum, VisualFunc > functionMap_;
};

//this is a simple singleton pattern
// you may access the controller wherever you are in code by calling
//TheController::Instance()->funcUsingController()

//[A] I can take this out if you want
class TheController
{
public:
    static Controller* Instance(){
        static Controller c;
        return &c;
    }
};
#endif