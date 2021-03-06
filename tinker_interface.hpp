#ifndef TINKER_INTERFACE_HPP
#define TINKER_INTERFACE_HPP

#include <cstdint>

/* Here is the minimal c++ side Fortran interface to tinker (see tinker_interface.f95 for fortran side)
 * 
 * Any Fortran subroutine should be called using only pointers, and the return type is always void
 * 
 * In C++ they should be declared within a extern "C" block
 * 
 */

#define TINKER_ARGSLEN 240

/**
 * @brief  This makes variables declared in the Fortran module tinker_cpp acessible from C++
 */
extern const int32_t natoms;
extern double* x;
extern double* y;
extern double* z;
extern double* vx;
extern double* vy;
extern double* vz;

extern "C"
{
  /**
  * @brief Provides the pseudo command line parameters to the tinker fortran code
  * 
  * @param n_args number of strings stored in arguments_concatenated : the total size of the arguments_concatenated string will be 240*n_args characters
  * @param arguments_concatenated a long string containing arguments : they are concatenated, each argument was a string of exactly 240 characters
  * 
  */
  void tinker_initialization(int32_t* n_args, char arguments_concatenated[]);
  
  /**
  * @brief Routine setting up integrator
  * 
  * @param numSteps Number of steps to perform
  * @param delta_t  The time step in picoseconds
  */
  void tinker_setup_integration(int32_t* numSteps, double* delta_t);
  

  /**
  * @brief Routine setting up simulation for NVT ensemble
  * 
  * @param temperature Temperature in Kelvin
  * @param tau_temp    Temperature coupling in ps
  */
  void tinker_setup_NVT(double* temperature, double* tau_temp);
  

  /**
  * @brief Routine setting up simulation for NPT ensemble
  * 
  * @param temperature  Temperature in Kelvin
  * @param press        Pressure in atmospheres
  * @param tau_temp     Temperature coupling in ps
  * @param tau_press    Pressure coupling in ps
  */
  void tinker_setup_NPT(double* temperature, double* press, double* tau_temp, double* tau_press);
  

  /**
  * @brief Routine for seeting frequency of writing to stdout or to traj files
  * 
  * NOTE This should be called after tinker_setup_NVT or tinker_setup_NPT
  * 
  * NOTE To disable I/O set those to a really large value
  * 
  * @param write_freq Freq for writing trajectory to archive file
  * @param print_freq Freq for writing info to stdout
  */
  void tinker_setup_IO(int32_t* write_freq, int32_t* print_freq);
  

  /**
  * @brief Perform one integration step
  * 
  * @param istep The current step number
  */
  void tinker_stochastic_one_step(int32_t* istep);
  
  /**
   * @brief Perform nsteps integration steps
   * 
   * @param istep  The current step number
   * @param nsteps The number of steps to perform
   */
  void tinker_stochastic_n_steps(int32_t* istep, int32_t* nsteps);
  
  /**
  * @brief Retrieve coordinates and velocities from Tinker
  * 
  * They will be stored in pointers x y z vx vy vz : they are of size natoms and have been allocated/freed by the fortran module.
  */
  void tinker_get_crdvels();
  
  /**
   * @brief Provide to Tinker x y z coordinates and vx vy vz velocities
   * 
   * They areretrieved from pointers x y z vx vy vz : they are of size natoms and have been allocated/freed by the fortran module.
   */  
  void tinker_set_crdvels();
  
  /**
  * @brief  Finalize the Tinker code
  * 
  */
  void tinker_finalize();
  
}

#endif /* TINKER_INTERFACE_HPP */
