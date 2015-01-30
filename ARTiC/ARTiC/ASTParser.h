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
enum CXCursorKind {
  /* Declarations */
  /**
  * \brief A declaration whose specific kind is not exposed via this
  * interface.
  *
  * Unexposed declarations have the same operations as any other kind
  * of declaration; one can extract their location information,
  * spelling, find their definitions, etc. However, the specific kind
  * of the declaration is not reported.
  */
  CXCursor_UnexposedDecl = 1,
  /** \brief A C or C++ struct. */
  CXCursor_StructDecl = 2,
  /** \brief A C or C++ union. */
  CXCursor_UnionDecl = 3,
  /** \brief A C++ class. */
  CXCursor_ClassDecl = 4,
  /** \brief An enumeration. */
  CXCursor_EnumDecl = 5,
  /**
  * \brief A field (in C) or non-static data member (in C++) in a
  * struct, union, or C++ class.
  */
  CXCursor_FieldDecl = 6,
  /** \brief An enumerator constant. */
  CXCursor_EnumConstantDecl = 7,
  /** \brief A function. */
  CXCursor_FunctionDecl = 8,
  /** \brief A variable. */
  CXCursor_VarDecl = 9,
  /** \brief A function or method parameter. */
  CXCursor_ParmDecl = 10,
  /** \brief An Objective-C \@interface. */
  CXCursor_ObjCInterfaceDecl = 11,
  /** \brief An Objective-C \@interface for a category. */
  CXCursor_ObjCCategoryDecl = 12,
  /** \brief An Objective-C \@protocol declaration. */
  CXCursor_ObjCProtocolDecl = 13,
  /** \brief An Objective-C \@property declaration. */
  CXCursor_ObjCPropertyDecl = 14,
  /** \brief An Objective-C instance variable. */
  CXCursor_ObjCIvarDecl = 15,
  /** \brief An Objective-C instance method. */
  CXCursor_ObjCInstanceMethodDecl = 16,
  /** \brief An Objective-C class method. */
  CXCursor_ObjCClassMethodDecl = 17,
  /** \brief An Objective-C \@implementation. */
  CXCursor_ObjCImplementationDecl = 18,
  /** \brief An Objective-C \@implementation for a category. */
  CXCursor_ObjCCategoryImplDecl = 19,
  /** \brief A typedef */
  CXCursor_TypedefDecl = 20,
  /** \brief A C++ class method. */
  CXCursor_CXXMethod = 21,
  /** \brief A C++ namespace. */
  CXCursor_Namespace = 22,
  /** \brief A linkage specification, e.g. 'extern "C"'. */
  CXCursor_LinkageSpec = 23,
  /** \brief A C++ constructor. */
  CXCursor_Constructor = 24,
  /** \brief A C++ destructor. */
  CXCursor_Destructor = 25,
  /** \brief A C++ conversion function. */
  CXCursor_ConversionFunction = 26,
  /** \brief A C++ template type parameter. */
  CXCursor_TemplateTypeParameter = 27,
  /** \brief A C++ non-type template parameter. */
  CXCursor_NonTypeTemplateParameter = 28,
  /** \brief A C++ template template parameter. */
  CXCursor_TemplateTemplateParameter = 29,
  /** \brief A C++ function template. */
  CXCursor_FunctionTemplate = 30,
  /** \brief A C++ class template. */
  CXCursor_ClassTemplate = 31,
  /** \brief A C++ class template partial specialization. */
  CXCursor_ClassTemplatePartialSpecialization = 32,
  /** \brief A C++ namespace alias declaration. */
  CXCursor_NamespaceAlias = 33,
  /** \brief A C++ using directive. */
  CXCursor_UsingDirective = 34,
  /** \brief A C++ using declaration. */
  CXCursor_UsingDeclaration = 35,
  /** \brief A C++ alias declaration */
  CXCursor_TypeAliasDecl = 36,
  /** \brief An Objective-C \@synthesize definition. */
  CXCursor_ObjCSynthesizeDecl = 37,
  /** \brief An Objective-C \@dynamic definition. */
  CXCursor_ObjCDynamicDecl = 38,
  /** \brief An access specifier. */
  CXCursor_CXXAccessSpecifier = 39,

  CXCursor_FirstDecl = CXCursor_UnexposedDecl,
  CXCursor_LastDecl = CXCursor_CXXAccessSpecifier,

  /* References */
  CXCursor_FirstRef = 40, /* Decl references */
  CXCursor_ObjCSuperClassRef = 40,
  CXCursor_ObjCProtocolRef = 41,
  CXCursor_ObjCClassRef = 42,
  /**
  * \brief A reference to a type declaration.
  *
  * A type reference occurs anywhere where a type is named but not
  * declared. For example, given:
  *
  * \code
  * typedef unsigned size_type;
  * size_type size;
  * \endcode
  *
  * The typedef is a declaration of size_type (CXCursor_TypedefDecl),
  * while the type of the variable "size" is referenced. The cursor
  * referenced by the type of size is the typedef for size_type.
  */
  CXCursor_TypeRef = 43,
  CXCursor_CXXBaseSpecifier = 44,
  /**
  * \brief A reference to a class template, function template, template
  * template parameter, or class template partial specialization.
  */
  CXCursor_TemplateRef = 45,
  /**
  * \brief A reference to a namespace or namespace alias.
  */
  CXCursor_NamespaceRef = 46,
  /**
  * \brief A reference to a member of a struct, union, or class that occurs in
  * some non-expression context, e.g., a designated initializer.
  */
  CXCursor_MemberRef = 47,
  /**
  * \brief A reference to a labeled statement.
  *
  * This cursor kind is used to describe the jump to "start_over" in the
  * goto statement in the following example:
  *
  * \code
  *   start_over:
  *     ++counter;
  *
  *     goto start_over;
  * \endcode
  *
  * A label reference cursor refers to a label statement.
  */
  CXCursor_LabelRef = 48,

  /**
  * \brief A reference to a set of overloaded functions or function templates
  * that has not yet been resolved to a specific function or function template.
  *
  * An overloaded declaration reference cursor occurs in C++ templates where
  * a dependent name refers to a function. For example:
  *
  * \code
  * template<typename T> void swap(T&, T&);
  *
  * struct X { ... };
  * void swap(X&, X&);
  *
  * template<typename T>
  * void reverse(T* first, T* last) {
  *   while (first < last - 1) {
  *     swap(*first, *--last);
  *     ++first;
  *   }
  * }
  *
  * struct Y { };
  * void swap(Y&, Y&);
  * \endcode
  *
  * Here, the identifier "swap" is associated with an overloaded declaration
  * reference. In the template definition, "swap" refers to either of the two
  * "swap" functions declared above, so both results will be available. At
  * instantiation time, "swap" may also refer to other functions found via
  * argument-dependent lookup (e.g., the "swap" function at the end of the
  * example).
  *
  * The functions \c clang_getNumOverloadedDecls() and
  * \c clang_getOverloadedDecl() can be used to retrieve the definitions
  * referenced by this cursor.
  */
  CXCursor_OverloadedDeclRef = 49,

  /**
  * \brief A reference to a variable that occurs in some non-expression
  * context, e.g., a C++ lambda capture list.
  */
  CXCursor_VariableRef = 50,

  CXCursor_LastRef = CXCursor_VariableRef,

  /* Error conditions */
  CXCursor_FirstInvalid = 70,
  CXCursor_InvalidFile = 70,
  CXCursor_NoDeclFound = 71,
  CXCursor_NotImplemented = 72,
  CXCursor_InvalidCode = 73,
  CXCursor_LastInvalid = CXCursor_InvalidCode,

  /* Expressions */
  CXCursor_FirstExpr = 100,

  /**
  * \brief An expression whose specific kind is not exposed via this
  * interface.
  *
  * Unexposed expressions have the same operations as any other kind
  * of expression; one can extract their location information,
  * spelling, children, etc. However, the specific kind of the
  * expression is not reported.
  */
  CXCursor_UnexposedExpr = 100,

  /**
  * \brief An expression that refers to some value declaration, such
  * as a function, variable, or enumerator.
  */
  CXCursor_DeclRefExpr = 101,

  /**
  * \brief An expression that refers to a member of a struct, union,
  * class, Objective-C class, etc.
  */
  CXCursor_MemberRefExpr = 102,

  /** \brief An expression that calls a function. */
  CXCursor_CallExpr = 103,

  /** \brief An expression that sends a message to an Objective-C
  object or class. */
  CXCursor_ObjCMessageExpr = 104,

  /** \brief An expression that represents a block literal. */
  CXCursor_BlockExpr = 105,

  /** \brief An integer literal.
  */
  CXCursor_IntegerLiteral = 106,

  /** \brief A floating point number literal.
  */
  CXCursor_FloatingLiteral = 107,

  /** \brief An imaginary number literal.
  */
  CXCursor_ImaginaryLiteral = 108,

  /** \brief A string literal.
  */
  CXCursor_StringLiteral = 109,

  /** \brief A character literal.
  */
  CXCursor_CharacterLiteral = 110,

  /** \brief A parenthesized expression, e.g. "(1)".
  *
  * This AST node is only formed if full location information is requested.
  */
  CXCursor_ParenExpr = 111,

  /** \brief This represents the unary-expression's (except sizeof and
  * alignof).
  */
  CXCursor_UnaryOperator = 112,

  /** \brief [C99 6.5.2.1] Array Subscripting.
  */
  CXCursor_ArraySubscriptExpr = 113,

  /** \brief A builtin binary operation expression such as "x + y" or
  * "x <= y".
  */
  CXCursor_BinaryOperator = 114,

  /** \brief Compound assignment such as "+=".
  */
  CXCursor_CompoundAssignOperator = 115,

  /** \brief The ?: ternary operator.
  */
  CXCursor_ConditionalOperator = 116,

  /** \brief An explicit cast in C (C99 6.5.4) or a C-style cast in C++
  * (C++ [expr.cast]), which uses the syntax (Type)expr.
  *
  * For example: (int)f.
  */
  CXCursor_CStyleCastExpr = 117,

  /** \brief [C99 6.5.2.5]
  */
  CXCursor_CompoundLiteralExpr = 118,

  /** \brief Describes an C or C++ initializer list.
  */
  CXCursor_InitListExpr = 119,

  /** \brief The GNU address of label extension, representing &&label.
  */
  CXCursor_AddrLabelExpr = 120,

  /** \brief This is the GNU Statement Expression extension: ({int X=4; X;})
  */
  CXCursor_StmtExpr = 121,

  /** \brief Represents a C11 generic selection.
  */
  CXCursor_GenericSelectionExpr = 122,

  /** \brief Implements the GNU __null extension, which is a name for a null
  * pointer constant that has integral type (e.g., int or long) and is the same
  * size and alignment as a pointer.
  *
  * The __null extension is typically only used by system headers, which define
  * NULL as __null in C++ rather than using 0 (which is an integer that may not
  * match the size of a pointer).
  */
  CXCursor_GNUNullExpr = 123,

  /** \brief C++'s static_cast<> expression.
  */
  CXCursor_CXXStaticCastExpr = 124,

  /** \brief C++'s dynamic_cast<> expression.
  */
  CXCursor_CXXDynamicCastExpr = 125,

  /** \brief C++'s reinterpret_cast<> expression.
  */
  CXCursor_CXXReinterpretCastExpr = 126,

  /** \brief C++'s const_cast<> expression.
  */
  CXCursor_CXXConstCastExpr = 127,

  /** \brief Represents an explicit C++ type conversion that uses "functional"
  * notion (C++ [expr.type.conv]).
  *
  * Example:
  * \code
  *   x = int(0.5);
  * \endcode
  */
  CXCursor_CXXFunctionalCastExpr = 128,

  /** \brief A C++ typeid expression (C++ [expr.typeid]).
  */
  CXCursor_CXXTypeidExpr = 129,

  /** \brief [C++ 2.13.5] C++ Boolean Literal.
  */
  CXCursor_CXXBoolLiteralExpr = 130,

  /** \brief [C++0x 2.14.7] C++ Pointer Literal.
  */
  CXCursor_CXXNullPtrLiteralExpr = 131,

  /** \brief Represents the "this" expression in C++
  */
  CXCursor_CXXThisExpr = 132,

  /** \brief [C++ 15] C++ Throw Expression.
  *
  * This handles 'throw' and 'throw' assignment-expression. When
  * assignment-expression isn't present, Op will be null.
  */
  CXCursor_CXXThrowExpr = 133,

  /** \brief A new expression for memory allocation and constructor calls, e.g:
  * "new CXXNewExpr(foo)".
  */
  CXCursor_CXXNewExpr = 134,

  /** \brief A delete expression for memory deallocation and destructor calls,
  * e.g. "delete[] pArray".
  */
  CXCursor_CXXDeleteExpr = 135,

  /** \brief A unary expression.
  */
  CXCursor_UnaryExpr = 136,

  /** \brief An Objective-C string literal i.e. @"foo".
  */
  CXCursor_ObjCStringLiteral = 137,

  /** \brief An Objective-C \@encode expression.
  */
  CXCursor_ObjCEncodeExpr = 138,

  /** \brief An Objective-C \@selector expression.
  */
  CXCursor_ObjCSelectorExpr = 139,

  /** \brief An Objective-C \@protocol expression.
  */
  CXCursor_ObjCProtocolExpr = 140,

  /** \brief An Objective-C "bridged" cast expression, which casts between
  * Objective-C pointers and C pointers, transferring ownership in the process.
  *
  * \code
  *   NSString *str = (__bridge_transfer NSString *)CFCreateString();
  * \endcode
  */
  CXCursor_ObjCBridgedCastExpr = 141,

  /** \brief Represents a C++0x pack expansion that produces a sequence of
  * expressions.
  *
  * A pack expansion expression contains a pattern (which itself is an
  * expression) followed by an ellipsis. For example:
  *
  * \code
  * template<typename F, typename ...Types>
  * void forward(F f, Types &&...args) {
  *  f(static_cast<Types&&>(args)...);
  * }
  * \endcode
  */
  CXCursor_PackExpansionExpr = 142,

  /** \brief Represents an expression that computes the length of a parameter
  * pack.
  *
  * \code
  * template<typename ...Types>
  * struct count {
  *   static const unsigned value = sizeof...(Types);
  * };
  * \endcode
  */
  CXCursor_SizeOfPackExpr = 143,

  /* \brief Represents a C++ lambda expression that produces a local function
  * object.
  *
  * \code
  * void abssort(float *x, unsigned N) {
  *   std::sort(x, x + N,
  *             [](float a, float b) {
  *               return std::abs(a) < std::abs(b);
  *             });
  * }
  * \endcode
  */
  CXCursor_LambdaExpr = 144,

  /** \brief Objective-c Boolean Literal.
  */
  CXCursor_ObjCBoolLiteralExpr = 145,

  /** \brief Represents the "self" expression in an Objective-C method.
  */
  CXCursor_ObjCSelfExpr = 146,

  CXCursor_LastExpr = CXCursor_ObjCSelfExpr,

  /* Statements */
  CXCursor_FirstStmt = 200,
  /**
  * \brief A statement whose specific kind is not exposed via this
  * interface.
  *
  * Unexposed statements have the same operations as any other kind of
  * statement; one can extract their location information, spelling,
  * children, etc. However, the specific kind of the statement is not
  * reported.
  */
  CXCursor_UnexposedStmt = 200,

  /** \brief A labelled statement in a function.
  *
  * This cursor kind is used to describe the "start_over:" label statement in
  * the following example:
  *
  * \code
  *   start_over:
  *     ++counter;
  * \endcode
  *
  */
  CXCursor_LabelStmt = 201,

  /** \brief A group of statements like { stmt stmt }.
  *
  * This cursor kind is used to describe compound statements, e.g. function
  * bodies.
  */
  CXCursor_CompoundStmt = 202,

  /** \brief A case statement.
  */
  CXCursor_CaseStmt = 203,

  /** \brief A default statement.
  */
  CXCursor_DefaultStmt = 204,

  /** \brief An if statement
  */
  CXCursor_IfStmt = 205,

  /** \brief A switch statement.
  */
  CXCursor_SwitchStmt = 206,

  /** \brief A while statement.
  */
  CXCursor_WhileStmt = 207,

  /** \brief A do statement.
  */
  CXCursor_DoStmt = 208,

  /** \brief A for statement.
  */
  CXCursor_ForStmt = 209,

  /** \brief A goto statement.
  */
  CXCursor_GotoStmt = 210,

  /** \brief An indirect goto statement.
  */
  CXCursor_IndirectGotoStmt = 211,

  /** \brief A continue statement.
  */
  CXCursor_ContinueStmt = 212,

  /** \brief A break statement.
  */
  CXCursor_BreakStmt = 213,

  /** \brief A return statement.
  */
  CXCursor_ReturnStmt = 214,

  /** \brief A GCC inline assembly statement extension.
  */
  CXCursor_GCCAsmStmt = 215,
  CXCursor_AsmStmt = CXCursor_GCCAsmStmt,

  /** \brief Objective-C's overall \@try-\@catch-\@finally statement.
  */
  CXCursor_ObjCAtTryStmt = 216,

  /** \brief Objective-C's \@catch statement.
  */
  CXCursor_ObjCAtCatchStmt = 217,

  /** \brief Objective-C's \@finally statement.
  */
  CXCursor_ObjCAtFinallyStmt = 218,

  /** \brief Objective-C's \@throw statement.
  */
  CXCursor_ObjCAtThrowStmt = 219,

  /** \brief Objective-C's \@synchronized statement.
  */
  CXCursor_ObjCAtSynchronizedStmt = 220,

  /** \brief Objective-C's autorelease pool statement.
  */
  CXCursor_ObjCAutoreleasePoolStmt = 221,

  /** \brief Objective-C's collection statement.
  */
  CXCursor_ObjCForCollectionStmt = 222,

  /** \brief C++'s catch statement.
  */
  CXCursor_CXXCatchStmt = 223,

  /** \brief C++'s try statement.
  */
  CXCursor_CXXTryStmt = 224,

  /** \brief C++'s for (* : *) statement.
  */
  CXCursor_CXXForRangeStmt = 225,

  /** \brief Windows Structured Exception Handling's try statement.
  */
  CXCursor_SEHTryStmt = 226,

  /** \brief Windows Structured Exception Handling's except statement.
  */
  CXCursor_SEHExceptStmt = 227,

  /** \brief Windows Structured Exception Handling's finally statement.
  */
  CXCursor_SEHFinallyStmt = 228,

  /** \brief A MS inline assembly statement extension.
  */
  CXCursor_MSAsmStmt = 229,

  /** \brief The null statement ";": C99 6.8.3p3.
  *
  * This cursor kind is used to describe the null statement.
  */
  CXCursor_NullStmt = 230,

  /** \brief Adaptor class for mixing declarations with statements and
  * expressions.
  */
  CXCursor_DeclStmt = 231,

  /** \brief OpenMP parallel directive.
  */
  CXCursor_OMPParallelDirective = 232,

  /** \brief OpenMP SIMD directive.
  */
  CXCursor_OMPSimdDirective = 233,

  /** \brief OpenMP for directive.
  */
  CXCursor_OMPForDirective = 234,

  /** \brief OpenMP sections directive.
  */
  CXCursor_OMPSectionsDirective = 235,

  /** \brief OpenMP section directive.
  */
  CXCursor_OMPSectionDirective = 236,

  /** \brief OpenMP single directive.
  */
  CXCursor_OMPSingleDirective = 237,

  /** \brief OpenMP parallel for directive.
  */
  CXCursor_OMPParallelForDirective = 238,

  /** \brief OpenMP parallel sections directive.
  */
  CXCursor_OMPParallelSectionsDirective = 239,

  /** \brief OpenMP task directive.
  */
  CXCursor_OMPTaskDirective = 240,

  /** \brief OpenMP master directive.
  */
  CXCursor_OMPMasterDirective = 241,

  /** \brief OpenMP critical directive.
  */
  CXCursor_OMPCriticalDirective = 242,

  /** \brief OpenMP taskyield directive.
  */
  CXCursor_OMPTaskyieldDirective = 243,

  /** \brief OpenMP barrier directive.
  */
  CXCursor_OMPBarrierDirective = 244,

  /** \brief OpenMP taskwait directive.
  */
  CXCursor_OMPTaskwaitDirective = 245,

  /** \brief OpenMP flush directive.
  */
  CXCursor_OMPFlushDirective = 246,

  /** \brief Windows Structured Exception Handling's leave statement.
  */
  CXCursor_SEHLeaveStmt = 247,

  /** \brief OpenMP ordered directive.
  */
  CXCursor_OMPOrderedDirective = 248,

  /** \brief OpenMP atomic directive.
  */
  CXCursor_OMPAtomicDirective = 249,

  /** \brief OpenMP for SIMD directive.
  */
  CXCursor_OMPForSimdDirective = 250,

  /** \brief OpenMP parallel for SIMD directive.
  */
  CXCursor_OMPParallelForSimdDirective = 251,

  /** \brief OpenMP target directive.
  */
  CXCursor_OMPTargetDirective = 252,

  /** \brief OpenMP teams directive.
  */
  CXCursor_OMPTeamsDirective = 253,

  CXCursor_LastStmt = CXCursor_OMPTeamsDirective,

  /**
  * \brief Cursor that represents the translation unit itself.
  *
  * The translation unit cursor exists primarily to act as the root
  * cursor for traversing the contents of a translation unit.
  */
  CXCursor_TranslationUnit = 300,

  /* Attributes */
  CXCursor_FirstAttr = 400,  
  CXCursor_UnexposedAttr = 400,
  CXCursor_IBActionAttr = 401,
  CXCursor_IBOutletAttr = 402,
  CXCursor_IBOutletCollectionAttr = 403,
  CXCursor_CXXFinalAttr = 404,
  CXCursor_CXXOverrideAttr = 405,
  CXCursor_AnnotateAttr = 406,
  CXCursor_AsmLabelAttr = 407,
  CXCursor_PackedAttr = 408,
  CXCursor_PureAttr = 409,
  CXCursor_ConstAttr = 410,
  CXCursor_NoDuplicateAttr = 411,
  CXCursor_CUDAConstantAttr = 412,
  CXCursor_CUDADeviceAttr = 413,
  CXCursor_CUDAGlobalAttr = 414,
  CXCursor_CUDAHostAttr = 415,
  CXCursor_CUDASharedAttr = 416,
  CXCursor_LastAttr = CXCursor_CUDASharedAttr,

  /* Preprocessing */
  CXCursor_PreprocessingDirective = 500,
  CXCursor_MacroDefinition = 501,
  CXCursor_MacroExpansion = 502,
  CXCursor_MacroInstantiation = CXCursor_MacroExpansion,
  CXCursor_InclusionDirective = 503,
  CXCursor_FirstPreprocessing = CXCursor_PreprocessingDirective,
  CXCursor_LastPreprocessing = CXCursor_InclusionDirective,
  CXCursor_ModuleImportDecl = 600,
  CXCursor_FirstExtraDecl = CXCursor_ModuleImportDecl,
  CXCursor_LastExtraDecl = CXCursor_ModuleImportDecl
};

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
        numFunctions++;
        string funcName = func->getNameInfo().getName().getAsString();
        if (funcName == "do_math") {
            rewriter.ReplaceText(func->getLocation(), funcName.length(), "add5");
            errs() << "** Rewrote function def: " << funcName << "\n";
        }
        
        return true;
    }

    virtual bool VisitStmt(Stmt *st) {
        if (ReturnStmt *ret = dyn_cast<ReturnStmt>(st)) {
            rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
            errs() << "** Rewrote ReturnStmt\n";
        }
        if (CallExpr *call = dyn_cast<CallExpr>(st)) {
            rewriter.ReplaceText(call->getLocStart(), 7, "add5");
            errs() << "** Rewrote function call\n";
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