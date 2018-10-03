#include <cstdlib>
#include <cstdio>
#include <cstring>

// #include <iostream>

#include <vector>
#include <array>

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
  
//   const char* argv1 = "diamond/diamond.xyz";
//   const char* argv2 = "diamond/mm2.prm";
  
  const char* argv1 = "enkephalin/enkephalin.xyz";
  const char* argv2 = "enkephalin/mm3pro.prm";
  
//   vector<array<char,240>> args;
//   array<char,240> a;
//   args.push_back(array<char,240>("tinker_cpp_itf"));
  
  int32_t n_args = 3;
  char* args = (char*) malloc(n_args*ARGSLEN*sizeof(char));
  
  memset(args,' ',n_args*ARGSLEN);
  
  memcpy(args,argv0,strlen(argv0)*sizeof(char));
  memcpy(args+ARGSLEN,argv1,strlen(argv1)*sizeof(char));
  memcpy(args+2*ARGSLEN,argv2,strlen(argv2)*sizeof(char));
  
  tinker_initialization(&n_args,args);

  // number of steps and timestep in ps
  int32_t nsteps = 25000;
  double dt = 0.002;
  tinker_setup_integration(&nsteps, &dt);
  
  // Setup NPT or NVT
//   double pressure = 1.0; // in atm
  double temperature = 300.0; // in Kelvin
  double tau_temp = 0.1; // temperature coupling in ps
//   double tau_press = 1.0; // pressure coupling in ps
  
//   tinker_setup_NPT(&temperature,&pressure,&tau_temp,&tau_press);
  tinker_setup_NVT(&temperature, &tau_temp);
  
  int32_t istep = 1;
//   int32_t nstep = 1000;
  tinker_stochastic_n_steps(&istep,&nsteps);
  
  tinker_finalize();

  return EXIT_SUCCESS;
}
