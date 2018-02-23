
! will call initial(), getxyz() and mechanic() from tinker,
!  first taking care of adding c command line arguments
subroutine do_initialization(arg1,arg2)
  
  use iso_c_binding
  use iounit
  use argue
  
  implicit none

  character(len=240,kind=c_char) :: arg1,arg2
  
  character(len=240) :: test_str
  logical            :: test
  
  ! first call the tinker routine initializing variables, parsing command line (but we will fill it manually with arguments below), etc.
  call initial

!   write (iout,*) narg
!   write (iout,*) listarg
  
  ! add pseudo command line arguments
!   write (iout,*) 'arg1 = ',arg1
!   write (iout,*) 'arg2 = ',arg2

  narg = 2
  arg(0) = arg1
  arg(1) = arg2
  listarg(0) = .false.
  listarg(1) = .true.
  
!   call nextarg(test_str,test)
!   write (iout,*) 'test_str = ',test_str
!   write (iout,*) 'test = ',test
  
!   write (iout,*) 'narg (after) = ',narg
  
  ! now we have added the fake command line arguments to variables of the the argue module so we can continue tinker initialization
  call getxyz
  call mechanic

end subroutine
