#ifndef QT_VISUALIZER_H_INCLUDED
#define QT_VISUALIZER_H_INCLUDED

#include "Visualizer.h"
#include "Controller.h"
#include "TypeEnum.h"

#include <vector>
#include <string>


/// This class QTVisualizer has been writen taking into account the example TextVisualizer
///
///   Until finding a better solution to the 'volatility' of the AST Nodes we have tryed to write 
///     an ASTReader that will go through the whole code, calling functions from this visualizer
///     whenever a given element is found. 
///   We are still looking for a more elegant solution of accesing to the ASTNodes without having 
///     to store them locally. If you, reading this, happen to have a solution to that problem
///     feel free to tell us!
///
class QTVisualizer :public Visualizer
{
public:
  QTVisualizer() :hasPrinted_(false)
    {}
  ~QTVisualizer()
    {}

    ///This function is not called in this application, but it may be called in others
    // this function will be called from an eventual loop.
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

    ///This is meant to initialization of the Visualizer
    virtual void Init()override
    {
      printf(" \nThe size is... %i", funcs_.size());
      funcs_.clear();
      printf(" and now... %i\n", funcs_.size());
    }

    ///This function will receive a controller and add to the controller the desired functions giving a 'tag' to
    // be able to access to them later on
    virtual void SetController(Controller* c)override
    { 
      printf("Adding new functions!!!\n");
        c->AddFunction((Controller::VisualFunc)RegisterFunctionDecl, TypeEnum::FuncDecl_Type);
        c->AddFunction((Controller::VisualFunc)RegisterReturnCall, TypeEnum::ReturnStm_Type);
        c->AddFunction((Controller::VisualFunc)RegisterVarDecl, TypeEnum::VarDecl_Type);
        //We are linking the function that will 'register' the code locally
        c->AddFunction((Controller::VisualFunc)RegisterCode, TypeEnum::Source_Code);
    }

    ///This function will be called whenever is a FunctionDecl is found in the ASTReader
    //It will store locally the names of the functions
    //This can be expandable to store more information from the functionDecl
    static void RegisterFunctionDecl(void * v)
    {
      printf("Adding a new function!!! Num of functions %i\n", funcs_.size());
      
      FunctionDecl* func = (FunctionDecl*)v;
      funcs_.push_back(new string(func->getNameInfo().getName().getAsString()));
    }

    ///This function will be called whenever is a Return call is found in the ASTReader
    //Currently it's empty, but potentially could obtain some information from the return
    static void RegisterReturnCall(void *v)
    {
        ReturnStmt* stm = (ReturnStmt*)v;
        //printf("Return found\n");
    }

    ///This function will be called whenever a variable is found in the ASTReader
    //Currently it's empty, but potentially could obtain some information from the return
    static void RegisterVarDecl(void *v)
    {
        VarDecl* var = (VarDecl*)v;
        //printf("%s: Variable declared\n", var->getNameAsString().c_str());
        variables_.push_back(new string(var->getNameAsString().c_str()));
    }

    ///This function will be called at the begining of the ASTProcess
    static void RegisterCode(void * v)
    {
      llvm::MemoryBuffer* buffer_temp = (llvm::MemoryBuffer*)v;
      buffer_ = std::string(buffer_temp->getBufferStart(), buffer_temp->getBufferSize());
    }

    ///This function will return a pointer to the buffer of the code (from the MODEL)
    ///  This function will return a pointer to the std:string. 
    static std::string* get_code(){
      return &buffer_;
    }

    ///This function will return a pointer to a vector of 'functions names'(from the MODEL)
    static std::vector<std::string*>* get_functions(){
      return &funcs_;
    }
    ///This function will return a pointer to a vector of 'variable names'(from the MODEL)
    static std::vector<std::string*>* get_variables(){
      return &variables_;
    }
private:
    bool hasPrinted_; 
   //Contains the source code
    static std::string buffer_;
   //Contains a vector with the name of functions.
    //Finding a way to instantiate functionDecl, this could be "improved" to store those
    static std::vector<std::string*> funcs_;
    static std::vector<std::string*> variables_;
};

std::vector<std::string*> QTVisualizer::funcs_;
std::vector<std::string*> QTVisualizer::variables_;
std::string QTVisualizer::buffer_;

#endif