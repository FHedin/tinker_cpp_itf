//-----------------------------------------------------------------------------------
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
   * routine initializing variables, managing pseudo-command line
   */
  void do_tinker_initialization(char arg1[240], char arg2[240]);
  
  /**
   * routine setting up integrator
   */
//   void do_tinker_setup_integration(int32_t* nsteps, double* dt);
  
  /**
   * routine setting up simulation for NVT ensemble
   */
  void do_tinker_setup_NVT(double* temperature);
  
  /**
   * routine setting up simulation for NPT ensemble
   */
  void do_tinker_setup_NPT(double* temperature, double* press);
  
}
