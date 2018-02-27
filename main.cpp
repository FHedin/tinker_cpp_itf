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
    fprintf(stderr,"Need one argument only: the name of the .xyz file to send to tinker\n");
    exit(-1);
  }
  
  // this is for transmitting command line arguments to the fortran interface, then forwarded to tinker
  char arg0[240],arg1[240];
  memset(arg0,' ',240);
  memset(arg1,' ',240);
  memcpy(arg0,argv[0],strlen(argv[0])*sizeof(char));
  memcpy(arg1,argv[1],strlen(argv[1])*sizeof(char));
  do_tinker_initialization(arg0,arg1);

  // number of steps and timestep in fs
  int32_t nsteps = 1000;
  double dt = 1.0;
  do_tinker_setup_integration(&nsteps, &dt);
  
  // Setup NPT or NVT
  double pressure = 1.0; // in atm
  double temperature = 300.0; // in Kelvin
  double tau_temp = 1.0; // temperature coupling in ps^-1
  double tau_press = 1.0; // pressure coupling in ps^-1
  do_tinker_setup_NPT(&temperature,&pressure,&tau_temp,&tau_press);
//   do_tinker_setup_NVT(&temperature, &tau_temp);

  return EXIT_SUCCESS;
}
