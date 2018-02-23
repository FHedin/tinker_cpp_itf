
! will call initial(), getxyz() and mechanic() from tinker,
!  after having first forwarded c command line arguments.
subroutine do_tinker_initialization(arg1,arg2) bind(C, name="do_tinker_initialization")
  
  use iso_c_binding
  use iounit
  use argue
  use inform
  
  implicit none

  character(len=1,kind=c_char) :: arg1(240),arg2(240)
  integer :: i

! first call the tinker routine initializing variables, parsing command line (but we will fill it manually with arguments below), etc.
  call initial
  
!   write(iout,*) 'arg(0) = |',arg(0)(1:240),'|'
!   write(iout,*) 'arg(1) = |',arg(1)(1:240),'|'
  
  ! add pseudo command line arguments
  narg = 2
  
  do i=1,240
    arg(0)(i:i) = arg1(i)
    arg(1)(i:i) = arg2(i)
  end do

!   write(iout,*) 'arg(0) = |',arg(0)(1:240),'|'
!   write(iout,*) 'arg(1) = |',arg(1)(1:240),'|'

  listarg(0) = .false.
  listarg(1) = .true.

  ! force verbosity
  silent  = .false.
  verbose = .true.
  debug   = .true.
  
  ! now we have added the fake command line arguments to variables of the argue module so we can continue tinker initialization
  call getxyz
  call mechanic

end subroutine
