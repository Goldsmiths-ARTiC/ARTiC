ARTiC
=====

This project started as a... A LLVM backend for creation of APK files.  

But it has evolved to be a...C++ code visualizer built with LLVM and Clang. 

This is an educational tool that will help people without knowledge of C++ to give their first steps into this programming language. It will show them news and different ways to visualize C++ code, helping them to understand programming.

There are future ideas for this project, as evolve it (changing the user interface part and changing the AST importer part -changing everything, actually) into a Graphical C++ IDE.

How to compile this project!:

1) Download llvm to the \llvm folder

          cd llvm
          %  git clone http://llvm.org/git/llvm.git

2) Download clang to the \llvm\tools folder

          cd llvm/tools
          % git clone http://llvm.org/git/clang.git

3) Build LLVM into the \build folder using CMAKE (you may have to download it as well!).

          Check this webpage! http://llvm.org/docs/CMake.html

4) Download Qt 5.4 (the community version!)

          http://www.qt.io/download/
          Be sure that you install the msvc2013_opengl compiler version!!!!!!!

5) Place into the \Qt\QtIncludes folder the following folders from the Qt installation folder ("Qt\5.4\msvc2013_opengl"):
mkspecs
include
lib

6) Place the dll files from the folder \Qt\release into the folder \ARTiC\ARTiC\Release

          Qt5Core.dll	
          Qt5Gui.dll	
          Qt5OpenGL.dll	
          Qt5Widgets.dll	
          icuin53.dll	
          icuuc53.dll
          

7) The solution of the project is \ARTiC\ARTiC.sln

8) The Qt project (to edit from the Qt Creator in case than needed is: Qt\UI.pro)


