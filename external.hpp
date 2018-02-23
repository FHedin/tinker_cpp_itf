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

  void do_tinker_initialization(char arg1[240], char arg2[240]);

}
