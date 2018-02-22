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
  __argue_MOD_narg = -2;
  
  // will print the tinker banner, and do some init
  initial_();
  
  cout << "Number of cmd lines args found by fortran is: " << __argue_MOD_narg << endl;
//   cout << "Verbosity ? " << __inform_MOD_verbose << endl;
  
  __inform_MOD_silent  = false;
  __inform_MOD_verbose = true;
  __inform_MOD_debug   = true;

//   cout << "Verbosity ? " << __inform_MOD_verbose << endl;
  
//   for(int i=0; i<21; i++)
//     cout << __argue_MOD_listarg[i] << "|";
//   cout << endl;
  
  // we put data manually in variables from module argue, mimicking arguments passed via command line

  // First be sure the argue module arrays are initialised properly
  for(int i=0;i<21;i++)
  {
    __argue_MOD_listarg[i] = false;
    
    for(int j=0;j<240;j++)
      __argue_MOD_arg[i][j] = ' ';
    
  }
  
  // we want to add 2 arguments
  __argue_MOD_narg = 2;
  
  cout << "Number of cmd lines args imposed: " << __argue_MOD_narg << endl;
  
  // add first argument (prog name)
  memcpy(__argue_MOD_arg[0],argv[0],(strlen(argv[0]))*sizeof(char));
  // this argument is not useful anyway so mark it false
  __argue_MOD_listarg[0] = false;
  
  // add second argument (name of xyz file)
  const char arg2[] = "waterbox";
  memcpy(__argue_MOD_arg[1],arg2,(strlen(arg2))*sizeof(char));
  __argue_MOD_listarg[1] = true;
  
  for(int i=0; i<21; i++)
    cout << __argue_MOD_listarg[i] << "|";
  cout << endl;
  
  // check if we can retrieve the arguments we have added
  char str[240];
  bool isOK=false;
  nextarg_(str,&isOK);
  cout << "isOk ? " << isOK << endl;
//     if(isOK)
  cout << "arg is: " << string(str) << endl;
  

//     
//   // will ask for and read a tinker xyz file interactively
//   // TODO find a way to provide it from command line
// //   getxyz_();
//   
//   // will setup the force field, energy functions, etc.
//   // it will automatically read and parse a key file with the same name as the xyz file
// //   mechanic_();
  
  return EXIT_SUCCESS;
}
