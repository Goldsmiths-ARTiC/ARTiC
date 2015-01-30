#ifndef TEXT_VISUALIZER_H_INCLUDED
#define TEXT_VISUALIZER_H_INCLUDED

#include "Visualizer.h"
#include "Controller.h"
#include "TypeEnum.h"

#include <vector>
#include <string>

class TextVisualizer :public Visualizer
{
public:
    TextVisualizer() :hasPrinted_(false)
    {}
    ~TextVisualizer()
    {}
    virtual void Update()override
    {
        if (!hasPrinted_)
        {
            hasPrinted_ = true;
            for (int i = 0; i < funcs_.size(); ++i)
            {
                printf("%s: Function found\n", funcs_[i]->c_str());
            }
            printf("Done!\n");
        }
    }

    virtual void Init()override
    {}

    virtual void SetController(Controller* c)override
    {
        c->AddFunction((Controller::VisualFunc)RegisterFunctionDecl, TypeEnum::FuncDecl_Type);
        c->AddFunction((Controller::VisualFunc)RegisterReturnCall, TypeEnum::ReturnStm_Type);
        c->AddFunction((Controller::VisualFunc)RegisterVarDecl, TypeEnum::VarDecl_Type);
    }

    static void RegisterFunctionDecl(void * v)
    {
        FunctionDecl* func = (FunctionDecl*)v;
        funcs_.push_back(new string(func->getNameInfo().getName().getAsString()));
    }
    static void RegisterReturnCall(void *v)
    {
        ReturnStmt* stm = (ReturnStmt*)v;
        printf("Return found\n");
    }

    static void RegisterVarDecl(void *v)
    {
        VarDecl* var = (VarDecl*)v;
        printf("%s: Variable declared\n", var->getNameAsString().c_str());
    }
private:
    bool hasPrinted_;
    static std::vector<std::string*> funcs_;
};

std::vector<std::string*> TextVisualizer::funcs_;

#endif