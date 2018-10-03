#include <cstdlib>
#include <cstdio>
#include <cstring>

// #include <iostream>

#include <vector>
#include <array>
#include <limits>
#include <chrono>

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
  
//   const char* argv1 = "enkephalin/enkephalin.xyz";
//   const char* argv2 = "enkephalin/mm3pro.prm";
  
  const char* argv1 = "ala2/ala2.xyz";
  const char* argv2 = "ala2/charmm22.prm";
  const int32_t natoms = 22;
  
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
  int32_t nsteps = 500000;
  double dt = 0.002;
  tinker_setup_integration(&nsteps, &dt);
  
  // Setup NPT or NVT
//   double pressure = 1.0; // in atm
  double temperature = 300.0; // in Kelvin
  double tau_temp = 0.1; // temperature coupling in ps
//   double tau_press = 1.0; // pressure coupling in ps
  
//   tinker_setup_NPT(&temperature,&pressure,&tau_temp,&tau_press);
  tinker_setup_NVT(&temperature, &tau_temp);

  // freq for writing trajectory to archive file
//   int32_t write_freq = (int32_t) 1.0/dt;
  int32_t write_freq = numeric_limits<int32_t>::max();
  // freq for writing info to stdout
//   int32_t print_freq = (int32_t) 1.0/dt;
  int32_t print_freq = numeric_limits<int32_t>::max();
  
  tinker_setup_IO(&write_freq,&print_freq);
  
  // allocate memory for storing coordinates and velocities of each atom
  vector<double> x(natoms);
  vector<double> y(natoms);
  vector<double> z(natoms);
  vector<double> vx(natoms);
  vector<double> vy(natoms);
  vector<double> vz(natoms);

  // allocate memory for retrieving atom type
  char* at_types = new char[natoms*4];
  
  // a simple xyz trajectory file
  FILE* xyzf = fopen("traj.xyz","wt");
  
  const int32_t traj_save_freq = 500;
  
  auto start = chrono::high_resolution_clock::now();

  for(int32_t istep=1; istep<=nsteps; istep++)
  {
    // perform one integration
    tinker_stochastic_one_step(&istep);
   
    // if necessary retrieve crdvels and print trajectory
    if(istep%traj_save_freq == 0)
    {
      double time = (double)istep*dt;
      
      fprintf(stdout,"Retrieving coordinates and velocities at time %.3lf ps\n",time);
      
      tinker_get_crdvels(x.data(),y.data(),z.data(),
                        vx.data(), vy.data(), vz.data(),
                        at_types);
      
      fprintf(xyzf,"%d\n",natoms);
      fprintf(xyzf,"Ala2 at time %.3lf\n",time);
      for(int32_t n=0; n<natoms; n++)
      {
        fprintf(xyzf,"%s \t %.8f \t %.8f \t %.8f \n",&(at_types[n*4]),x[n],y[n],z[n]);
      }
      
    }
    
  }
  
  //fclose(xyzf);
  
  tinker_finalize();
  
  delete[] at_types;

  auto end = chrono::high_resolution_clock::now();

  double elapsed_milli_seconds = (double) chrono::duration_cast<chrono::milliseconds>(end-start).count();

  printf("Dynamics took %lf seconds\n",elapsed_milli_seconds/1000.);
  printf("Performance is %lf ns/day\n",(((double)nsteps)*dt/1000.)/(elapsed_milli_seconds/1000./86400.));

  return EXIT_SUCCESS;
}
