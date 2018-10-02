#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <iostream>

// this contains the pseudo interface to tinker's fortran code
#include "external.hpp"

#define ARGSLEN 240

//-----------------------------------------------------------------------------------

using namespace std;

// this is a minimal C++ version of tinker's "dynamic" program
int main(/*int argc, char** argv*/)
{
//   if(argc != 2)
//   {
//     fprintf(stderr,"Need one argument only: the name of the .xyz file to send to tinker\n");
//     exit(-1);
//   }
  
  const char* argv0 = "tinker_cpp_itf";
  const char* argv1 = "enkephalin/enkephalin.xyz";
  const char* argv2 = "enkephalin/mm3pro.prm";
  
  int32_t n_args = 3;
  char* args = (char*) malloc(n_args*ARGSLEN*sizeof(char));
  
  memset(args,' ',n_args*ARGSLEN);
  
  memcpy(args,argv0,strlen(argv0)*sizeof(char));
  memcpy(args+ARGSLEN,argv1,strlen(argv1)*sizeof(char));
  memcpy(args+2*ARGSLEN,argv2,strlen(argv2)*sizeof(char));
  
  do_tinker_initialization(&n_args,args);

  // number of steps and timestep in fs
  int32_t nsteps = 1000;
  double dt = 1.0;
//   do_tinker_setup_integration(&nsteps, &dt);
  
  // Setup NPT or NVT
  double pressure = 1.0; // in atm
  double temperature = 300.0; // in Kelvin
  double tau_temp = 100.0; // temperature coupling in ps^-1
  double tau_press = 1.0; // pressure coupling in ps^-1
  
//   do_tinker_setup_NPT(&temperature,&pressure,&tau_temp,&tau_press);
//   do_tinker_setup_NVT(&temperature, &tau_temp);
  
  int32_t istep = 1;
  int32_t nstep = 1000;
//   do_tinker_stochastic_n_steps(&istep,&nstep);

  return EXIT_SUCCESS;
}
