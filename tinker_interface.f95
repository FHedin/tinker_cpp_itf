
! This is the Fortran code acting as an intermediate layer between Tinker and the C++ code
module tinker_cpp

  use iso_c_binding
  
  implicit none
  
  integer(kind=c_int32_t)         :: nsteps
  real(kind=c_double)             :: dt
  
  ! this variable is declared bound to C so that it can be accessed directly from C++ code
  integer(kind=c_int32_t),bind(C) :: natoms

  contains

  !---------------------------------------------------------------------------------------------------------
  
  ! will call initial(), getxyz() and mechanic() from tinker,
  !  after having first forwarded c command line arguments.
  subroutine tinker_initialization(n_args,args) bind(C, name="tinker_initialization")
    
    use argue, only: narg, listarg, arg
    use atoms, only: n
    use bath, only: kelvin, atmsph, isothermal, isobaric
    
    implicit none

    integer(kind=c_int32_t) :: n_args
    character(len=1,kind=c_char) :: args(n_args*240)
    
    integer :: i,j
    
    ! first call the tinker routine initializing variables, parsing command line
    ! (but we will fill it manually with arguments below), etc.
    call initial()
    
    ! add pseudo command line arguments
    narg = n_args
    
    do i=0,narg-1
      do j=1,240
        arg(i)(j:j) = args(i*240+j)
      end do
    end do

    listarg(0) = .false.
    do i=1,narg
      listarg(i) = .true.
    end do
    
    ! force verbosity
!     silent  = .false.
!     verbose = .true.
!     debug   = .true.

    ! disabled output ?
!     silent  = .true.
!     verbose = .false.
!     debug   = .false.
    
    ! now we have added the fake command line arguments to variables of the argue module so we can continue tinker initialization
    call getxyz()
    call mechanic()
    
    kelvin = 0.0d0
    atmsph = 0.0d0
    isothermal = .false.
    isobaric = .false.
    
    natoms = n

  end subroutine

  !---------------------------------------------------------------------------------------------------------

  ! setup the integrator : only stochastic verlet supported
  subroutine tinker_setup_integration(numSteps,delta_t) bind(C, name="tinker_setup_integration")
    
    implicit none
        
    integer(kind=c_int32_t) :: numSteps
    real(kind=c_double)     :: delta_t
    
!     integer(kind=c_int32_t) :: i
    
    nsteps = numSteps
    dt     = delta_t

!     integrate = 'STOCHASTIC'
    
  end subroutine

  !---------------------------------------------------------------------------------------------------------

  ! setup the simulation to take place in the NVT ensemble
  subroutine tinker_setup_NVT(temperature,tau_temperature) bind(C, name="tinker_setup_NVT")
    
    use bath, only: kelvin, isothermal, tautemp
    
    implicit none
    
    real(kind=c_double) :: temperature, tau_temperature
    
    kelvin = temperature
    isothermal = .true.
    
    tautemp = tau_temperature
    tautemp = max(tautemp,dt)
    
    call shakeup()
    call mdinit()
    
  end subroutine

  !---------------------------------------------------------------------------------------------------------

  ! setup the simulation to take place in the NPT ensemble
  subroutine tinker_setup_NPT(temperature,press,tau_temperature,tau_pressure) bind(C, name="tinker_setup_NPT")
    
    use bath, only: kelvin, atmsph, isothermal, isobaric, tautemp, taupres
    
    implicit none

    real(kind=c_double) :: temperature, press, tau_temperature, tau_pressure
    
    kelvin = temperature
    atmsph = press
    isothermal = .true.
    isobaric = .true.
    
    tautemp = tau_temperature
    taupres = tau_pressure
    
    ! enforce bounds on thermostat and barostat coupling times
    tautemp = max(tautemp,dt)
    taupres = max(taupres,dt)
    
    call shakeup()
    call mdinit()

  end subroutine
  
  ! setup Tinker's I/O frequency
  subroutine tinker_setup_IO(write_freq,print_freq) bind(C, name="tinker_setup_IO")
  
    use inform, only: iwrite, iprint
    
    implicit none
    
    integer(kind=c_int32_t) :: write_freq, print_freq
    
    iwrite = write_freq
    iprint = print_freq
    
  end subroutine

  !---------------------------------------------------------------------------------------------------------

  ! Performs one integration step (STOCHASTIC type integrator only)
  subroutine tinker_stochastic_one_step(istep) bind(C, name="tinker_stochastic_one_step")

    implicit none
    
    integer(kind=c_int32_t) :: istep
    
    call sdstep(istep,dt)
  
  end subroutine
  
  !---------------------------------------------------------------------------------------------------------
  
  ! Performs nsteps integration steps (STOCHASTIC type integrator only)
  subroutine tinker_stochastic_n_steps(istep,nsteps) bind(C, name="tinker_stochastic_n_steps")

    implicit none
    
    integer(kind=c_int32_t) :: istep, nsteps
    
    integer(kind=c_int32_t) :: i
    
    do i=1,nsteps
      call sdstep(istep,dt)
      istep = istep + 1
    end do
  
  end subroutine
  !---------------------------------------------------------------------------------------------------------
  
  ! Copy to C++ vectors the current coordinates and velocities
  subroutine tinker_get_crdvels(x_crd,y_crd,z_crd,x_vels,y_vels,z_vels,at_type) bind(C, name="tinker_get_crdvels")
  
    use atoms,  only: x,y,z,n
    use atomid, only: name
    use moldyn, only: v
  
    implicit none
    
    real(kind=c_double) :: x_crd(n), y_crd(n), z_crd(n)
    real(kind=c_double) :: x_vels(n), y_vels(n), z_vels(n)
    character(len=1,kind=c_char) :: at_type(4*n)
    
    integer(kind=c_int32_t) :: i,j
    
    x_crd(1:n) = x(1:n)
    y_crd(1:n) = y(1:n)
    z_crd(1:n) = z(1:n)
    
    x_vels(1:n) = v(1,1:n)
    y_vels(1:n) = v(2,1:n)
    z_vels(1:n) = v(3,1:n)
    
    do i=1,n
      j = (i-1)*4
      at_type(j+1:j+3) = name(i)(1:3)
      at_type(j+4)   = C_NULL_CHAR
    end do
    
  end subroutine
  
  !---------------------------------------------------------------------------------------------------------
  
  ! Finalize Tinker code properly 
  subroutine tinker_finalize() bind(C, name="tinker_finalize")

    implicit none
    
    call final()
  
  end subroutine
  
end module
