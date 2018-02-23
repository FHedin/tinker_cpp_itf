//-----------------------------------------------------------------------------------
/* Here is the minimal c++ side Fortran interface to tinker (see fortran_interface.f95 for fortran side)
 * 
 * Any Fortran subroutine shoul be called using only pointers, and the rerutn type is always void
 * 
 * An underscore _ should be added at the end of the subroutine name
 * 
 * In C++ they should be declared within a extern "C" block
 * 
 */

extern "C"
{

  void do_initialization_(char[240],char[240]);

}
