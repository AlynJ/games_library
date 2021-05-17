This is a project of creating a Minesweeper game using C++ wrapped in Python. The C++ code forms a library and Python is used to generate the GUI for the game. 

The purpose of this project is for the user to call upon the Minesweeper game and GUI within their own python script(s).

--------------------------------------------------------------------------------
SYSTEM REQUIREMENTS:

The system requirements for installation are:
  -cmake 3.10
  -GCC 7.5.0
  -Boost 1.65.1
  -Python 3.6.9
    --numpy 1.19.4
    --tkinter
 
This package has been tested using the aforementioned versions of the software and libraries.

--------------------------------------------------------------------------------
COMPILATION:

This code has only been tested Ubuntu and uses cmake to generate the Makefiles.

To compile the library, use the following commands:
  
  cd /path-to-Minesweeper/.
  mkdir build
  cd build
  cmake .. -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=/path-to-installation-directory/. 
  make
  make install

Note that the user will need to link the installation directory within their python code.

This package provides an example python script (example.py) which call upon the library. 

ALTERNATIVE:

Currently, the Minesweeper game can be used without the GUI.  
This terminal version is compiled with the following commands:
  
  cd /path-to-Minesweeper/.
  g++ src/C++/minesweeper_game.cpp src/C++/game.cpp -o minesweeper -I./include/ 

--------------------------------------------------------------------------------
FUTURE DEVELOPMENTS:

The aim of this project will be to include more games and expand this into a games library.

Potentially future games:
  Sudoku
  Connect-4
  Wordsearch

--------------------------------------------------------------------------------
TO DO:

  Minesweeper:
    Have user defined grid and mines.
