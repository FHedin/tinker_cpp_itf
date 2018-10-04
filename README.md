----------------------------------------------
# tinker_cpp_itf
----------------------------------------------

A basic and simple C++ interface to the Tinker Molecular Dynamics (MD) software.

This is **work in progress** !

See https://dasher.wustl.edu/tinker/ for information concerning the Tinker MD engine (written in Fortran).

Note that tinker's source code is not provided and should be downloaded and compiled separately.

----------------------------------------------
# DEPENDANCIES
----------------------------------------------

The only dependancies come from Tinker : the fftw3 and fftw3_threads libraries are required at linking.

----------------------------------------------
# COMPILE & INSTALL
----------------------------------------------

Use the Makefile provided by this project (simply execute "make" in your terminal after adjusting if required the content of the file) :
  * It is expected that Tinker is installed in the directory $(TINKER_HOME)
  * $(TINKER_HOME) should contains a directory "mods"" where are stored all the Fortran module files *.mod generated during compilation of the Tinker source code : this is stored in $(TINKER_MODS_DIR)
  * $(TINKER_HOME) should contain the static library "libtinker.a" generated during compilation of the Tinker source code : this is stored in $(TINKER_LIB)
  * $(CXX) $(FC) and $(OPTS) can be tuned for modifying the compilers and their options : it is highly recommended to use the same version of the Fortran compiler for both compiling Tinker and this interface. It is also recommended to use C++ and Fortran compilers of the same generation (e.g. g++ 6.4.0 with gfortran 6.4.0).
  * Use $(LIBS) for adjusting the name of the system fftw3 and fftw3_threads libraries if required.

----------------------------------------------
# LICENSING
----------------------------------------------

Files provided within this project are licensed under the following terms : 

Copyright (c) 2018, Florent Hédin, Tony Lelièvre, and École des Ponts - ParisTech
All rights reserved.

The 3-clause BSD license is applied to this software.

See LICENSE.txt

Tinker's source code is distributed under its own license (see https://dasher.wustl.edu/tinker/) and is NOT provided within this project (excepted for the test cases provided in a few subdirectories of this repository root).
