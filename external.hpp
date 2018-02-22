//-----------------------------------------------------------------------------------
/* Here is the minimal c++ Fortran interface to tinker
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
  
  // subroutine initial(): initialises silently many tinker variales and prints a banner to the terminal
  void initial_();
  
  // "getxyz" asks for a Cartesian coordinate file name,
  // then reads in the coordinates file
  void getxyz_();
  
  // "mechanic" sets up needed parameters for the potential energy
  // calculation and reads in many of the user selectable options
  void mechanic_();
  
  // retrieves an argument from command line
  // when passing a string the length follows, but exceptionally by vaue instead of by reference !!!!
  void nextarg_(char* string, bool* success);
}

/*
 * For accessing fortran data defined within module, it is necessary to declare them extern, but outside of the above extern "C"
 */

//from module inform:
// silent    logical flag to turn off all information printing
// verbose   logical flag to turn on extra information printing
// debug     logical flag to turn on full debug printing
extern "C" bool __inform_MOD_silent;
extern "C" bool __inform_MOD_verbose;
extern "C" bool __inform_MOD_debug;

// from module argue:
// narg = number of command line arguments found by fortran iargc ; we want to overide this manually
// arg  = array where command line arguments are stored
// listarg = array of logical, set to true if the argument is useful
extern "C" int  __argue_MOD_narg;
extern "C" char __argue_MOD_arg[21][240];
extern "C" bool __argue_MOD_listarg[21];

