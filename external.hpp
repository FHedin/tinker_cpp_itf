/* Here is the minimal c++ side Fortran interface to tinker (see fortran_interface.f95 for fortran side)
 * 
 * Any Fortran subroutine shoul be called using only pointers, and the return type is always void
 * 
 * In C++ they should be declared within a extern "C" block
 * 
 */

extern "C"
{


  /**
  * @brief Provides the pseudo command line parameters to the tinker fortran code
  * 
  * @param n_args number of strings stored in arguments_concatenated : the total size of the arguments_concatenated string will be 240*n_args characters
  * @param arguments_concatenated a long string containing arguments : they are concatenated, each argument was a string of exactly 240 characters
  * 
  */
  void do_tinker_initialization(int32_t* n_args, char arguments_concatenated[]);
  
  /**
   * routine setting up integrator
   */
  void do_tinker_setup_integration(int32_t* numSteps, double* delta_t);
  
  /**
   * routine setting up simulation for NVT ensemble
   */
  void do_tinker_setup_NVT(double* temperature, double* tau_temp);
  
  /**
   * routine setting up simulation for NPT ensemble
   */
  void do_tinker_setup_NPT(double* temperature, double* press, double* tau_temp, double* tau_press);
  
  /**
   * Perform one integration step 
   */
  void do_tinker_stochastic_one_step(int32_t* istep);
  
  /**
   * Perform n integration steps 
   */
  void do_tinker_stochastic_n_steps(int32_t* istep, int32_t* n);
  
}
