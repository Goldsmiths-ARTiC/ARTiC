#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <map>
#include <cstdio>
#include<functional>

//Ryan and Juanmihd make this class!!
class Visualizer;




class Controller
{
public:
    typedef std::function<void(void*)> VisualFunc;
public:
    Controller(){}
    Controller(const Controller&) = delete;
    const Controller& operator = (const Controller&) = delete;


    //The main loop, called with the AST tree in context
    void Loop(void)
    {
        printf("If you see this, this is the main loop.\nThere is no loop at the moment, try and come back later.\n");
        //system("PAUSE");
    }

    void SetVisualizer(Visualizer* vArg)
    {
        //do deattached
        v = vArg;
        //do attachment
    }
    //Add a function to the function map, callable by the name given
    bool AddFunction(VisualFunc& func, const char* name)
    {
        functionMap_[name] = func;


        //this is so this function can be called staically
        // for example using a global variable you may do...
        // static const bool call=AddFunction(stuff,stuff)
        // to execute the function before main
        return true;
    }

    //Call a function in the function map, given the name and a pointer for the argument
    void CallFunc(const char* name, void * info)
    {
        //calling a function in the map with data map
        functionMap_.at(name)(info);
    }

    
private:
    Visualizer* v;
    std::map<const char*, VisualFunc > functionMap_;
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