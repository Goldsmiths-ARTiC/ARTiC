#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "ASTParser.h"

class Visualizer;

class Controller
{
public:
    void Run(int argc,const char** argv)
    {
        reader = new ASTParser();
        reader->Init(argc, argv);
        reader->Read();

        printf("\n All Done! \n");


    }

    void SetVisualizer(Visualizer* vArg)
    {
        //do deattached
        v = vArg;
        //do attachment
    }
private:
    Visualizer* v;
    ASTParser * reader;
};


#endif