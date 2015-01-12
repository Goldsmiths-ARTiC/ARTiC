//@author Juanmi Huertas Delgado
//@brief This is a simple test for a Tooling application with LLVM
//  I just pretend to build an ASTReader that will run through the code, looking for some things to be readed
//  if it finds a declaration it will just print it out on the screen

#include "Controller.h"
int main(int argc, const char **argv) {
    Controller c;
    c.Run(argc, argv);
}
