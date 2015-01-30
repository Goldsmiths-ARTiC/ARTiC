#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "Controller.h"
#include "ASTParser.h"
#include "TextVisualizer.h"

class ExampleFrontendAction : public ASTFrontendAction {

public:// inherited member functions
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) {
        return std::unique_ptr<ASTConsumer>(new ExampleASTConsumer(&CI));
    }

    virtual void ExecuteAction()override
    {
        ASTFrontendAction::ExecuteAction();
        TheController::Instance()->Loop();
    }
};

class Init
{
public:

    //The first function to be called, it creates a frontend action to be executed
    //The application piggybacks on the frontend action, 
    //executing before the AST is deleted
    static void InitEverything(int argc, const char** argv)
    {
        llvm::cl::OptionCategory our_tool_category("Our tool option");
        CommonOptionsParser op(argc, argv, our_tool_category);
        // create a new Clang Tool instance (a LibTooling environment)
        ClangTool tool(op.getCompilations(), op.getSourcePathList());

        TheController::Instance()->SetVisualizer(new TextVisualizer());

        int result = tool.run(newFrontendActionFactory<ExampleFrontendAction>().get());
        //After this point our program has stopped executing and we have broken the main loop


        // print out the rewritten source code ("rewriter" is a global var.)

        rewriter.getEditBuffer(rewriter.getSourceMgr().getMainFileID()).write(errs());

    }
};

#endif