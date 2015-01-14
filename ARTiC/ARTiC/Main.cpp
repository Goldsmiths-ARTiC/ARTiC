/*
    We are hacking the frontend action to execute all our code
    before exiting.

    Init::InitEverything--\
                          |->FrontendAction::ExecuteAction-\
                                                            |-Controller::Loop()
                          /----------------<---------------/
                          |-Exit()
*/

#include "Init.h"
int main(int argc, const char **argv) {
    Init::InitEverything(argc,argv);
    return 0;
}
