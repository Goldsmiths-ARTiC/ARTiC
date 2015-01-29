To use the interface:

- We need to set up a new folder (QtIncludes) with all the needed files to be able to compile the application.
- We need to have the proper .dll files to be able to run the application.

To do:

- Build the U.I.
  - Re-compile the U.I. with msvc2013-opengl. (?)
  - Set up everything within the repository. (?)

- Connect U.I: and ASTReader.
  - QMainWindow
        \-----> Import Code:  (will call to ASTReader and then will ask the interface to draw).

- Draw AST Tree into the UI as text.
  - Be sure that we can write text (DONE!)
  - Obtain the code from ASTContext and input it into textlabel.

- Draw AST Tree into the UI as blobs.
  - Be sure that we can draw things 
  - Obtain the functions with the ASTReader and draw primitives with some text on them. (openGL)