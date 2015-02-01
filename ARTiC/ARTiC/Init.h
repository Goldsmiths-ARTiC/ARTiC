#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "Controller.h"
#include "ASTParser.h"
#include "QTVisualizer.h"

class ARTiCFrontendAction : public ASTFrontendAction {

public:// inherited member functions
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
      return std::unique_ptr<ASTConsumer>(new ARTiCASTConsumer(&CI));
    }

    virtual void ExecuteAction()override
    {
        ASTFrontendAction::ExecuteAction();

      //This loop for the controller has been commented as it is not strictly necessary.
      //After giving a look to the example TextVisualizer it doesn't seem necessary to use
      //this 'looping hack' to retain in context the AST Nodes, as -as seen in the TextVisualizer
      //example- all the desired content of the AST is being copied.
      //Therefore, for the QTVisualizer, it was taken the same approach. This approach actually
      //transform that visualizer classes, together with the Controller and this Init in the
      //Model of the application, that can be read from the Interface-Controller (QMainWindow)
        
        //TheController::Instance()->Loop();  
    }
};

class Init
{
public:

    //The first function to be called, it creates a frontend action to be executed
    //The application piggybacks on the frontend action, 
    //executing before the AST is deleted
    // The parameters have to be equivalent as when this is called from the command line
    static void InitEverything(int argc, const char** argv)
    {
        llvm::cl::OptionCategory our_tool_category("Our tool option");
        CommonOptionsParser op(argc, argv, our_tool_category);
        // create a new Clang Tool instance (a LibTooling environment)
        ClangTool tool(op.getCompilations(), op.getSourcePathList());

        //We set up the 
        TheController::Instance()->SetVisualizer(new QTVisualizer());

        int result = tool.run(newFrontendActionFactory<ARTiCFrontendAction>().get());
        //After this point our program has stopped executing and we have broken the main loop
        // print out the rewritten source code ("rewriter" is a global var.)

        //This line has been commented as it may not be necessary to re-write things in the console 
        //rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(errs());

    }
};

#endif