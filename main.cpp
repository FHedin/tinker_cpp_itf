#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <iostream>

// this contains the pseudo interface to tinker's fortran code
#include "external.hpp"

//-----------------------------------------------------------------------------------

using namespace std;

// this is a minimal C++ version of tinker's "dynamic" program
int main(int argc, char** argv)
{
  
  if(argc != 2)
  {
    fprintf(stderr,"Need one argument only: the name of the .xyz file to send to tinker");
    exit(-1);
  }
  
  // this is for transmitting command line arguments to the fortran interface, then forwarded to tinker
  char arg0[240],arg1[240];
  memset(arg0,' ',240);
  memset(arg1,' ',240);
  memcpy(arg0,argv[0],strlen(argv[0])*sizeof(char));
  memcpy(arg1,argv[1],strlen(argv[1])*sizeof(char));
  
  do_tinker_initialization(arg0,arg1);
 
  return EXIT_SUCCESS;
}
