#ifndef ASTREADER_H_INCLUDED
#define ASTREADER_H_INCLUDED

#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

Rewriter rewriter;
int numFunctions;

class ExampleVisitor : public RecursiveASTVisitor<ExampleVisitor> {
private:
    ASTContext *astContext; // used for getting additional AST info
public:
    explicit ExampleVisitor(CompilerInstance *CI)
        : astContext(&(CI->getASTContext())) // initialize private members
    {
        rewriter.setSourceMgr(astContext->getSourceManager(), astContext->getLangOpts());
    }

    virtual bool VisitFunctionDecl(FunctionDecl *func) {
        TheController::Instance()->CallFunc(TypeEnum::FuncDecl_Type, func);
        
        
        return true;
    }

    virtual bool VisitStmt(Stmt *st) {
        if (ReturnStmt *ret = dyn_cast<ReturnStmt>(st)) {
            TheController::Instance()->CallFunc(TypeEnum::ReturnStm_Type, st);
        }
        if (CallExpr *call = dyn_cast<CallExpr>(st)) {
            TheController::Instance()->CallFunc(TypeEnum::FuncCall_Type, st);
        }
        return true;
    }

    /*
    virtual bool VisitReturnStmt(ReturnStmt *ret) {
    rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
    errs() << "** Rewrote ReturnStmt\n";
    return true;
    }

    virtual bool VisitCallExpr(CallExpr *call) {
    rewriter.ReplaceText(call->getLocStart(), 7, "add5");
    errs() << "** Rewrote function call\n";
    return true;
    }
    */
};

class ExampleASTConsumer : public ASTConsumer {
private:
    ExampleVisitor *visitor; // doesn't have to be private

public:
    // override the constructor in order to pass CI
    explicit ExampleASTConsumer(CompilerInstance *CI)
        : visitor(new ExampleVisitor(CI)) // initialize the visitor
    { }

    // override this to call our ExampleVisitor on the entire source file
    virtual void HandleTranslationUnit(ASTContext &Context) {
        /* we can use ASTContext to get the TranslationUnitDecl, which is
        a single Decl that collectively represents the entire source file */
        printf("AST reading begins ...now!\n");

        visitor->TraverseDecl(Context.getTranslationUnitDecl());
    }
};
#endif