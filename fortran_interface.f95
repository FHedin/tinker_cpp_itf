
module tinker_cpp

  use iso_c_binding
  
  use bath, only: kelvin, atmsph, isothermal, isobaric, tautemp, taupres
  use mdstuf, only: integrate
  use inform, only: iwrite
  
  implicit none
  
  integer(kind=c_int32_t) :: nsteps
  real(kind=c_double)     :: dt

  public  :: do_tinker_initialization, do_tinker_setup_integration, do_tinker_setup_NVT, do_tinker_setup_NPT
  public  :: do_tinker_stochastic_one_step, do_tinker_stochastic_n_steps
  private :: nsteps, dt

  contains

  !---------------------------------------------------------------------------------------------------------
  
  ! will call initial(), getxyz() and mechanic() from tinker,
  !  after having first forwarded c command line arguments.
  subroutine do_tinker_initialization(arg1,arg2) bind(C, name="do_tinker_initialization")
    
!     use iounit
    use argue
    use inform
    
    implicit none

    character(len=1,kind=c_char) :: arg1(240),arg2(240)
    integer :: i
    
!     integer(kind=c_int32_t) :: a
!     
!     a=1
!     write(iout,*) huge(i),mod(5,huge(i))

!   iwrite = 1
    
  ! first call the tinker routine initializing variables, parsing command line
  ! (but we will fill it manually with arguments below), etc.
    call initial()
    
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
    call getxyz()
    call mechanic()
    
    kelvin = 0.0d0
    atmsph = 0.0d0
    isothermal = .false.
    isobaric = .false.

  end subroutine

  !---------------------------------------------------------------------------------------------------------

  ! setup the integrator : only stochastic verlet supported
  subroutine do_tinker_setup_integration(numSteps,delta_t) bind(C, name="do_tinker_setup_integration")
    
    implicit none
        
    integer(kind=c_int32_t) :: numSteps
    real(kind=c_double)     :: delta_t
    
    integer(kind=c_int32_t) :: i
    
    nsteps = numSteps
    dt     = delta_t

    integrate = 'STOCHASTIC'
    
    ! this is used in mod(currentStep,iwrite) in order to know if there should be a traj I/O in case result is zero
    ! by setting it to something huge (here the largest 32 bits integer), we disable I/O
    ! iwrite = huge(i)
    iwrite = 1
    
  end subroutine

  !---------------------------------------------------------------------------------------------------------

  ! setup the simulation to take place in the NVT ensemble
  subroutine do_tinker_setup_NVT(temperature,tau_temperature) bind(C, name="do_tinker_setup_NVT")
    
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
  subroutine do_tinker_setup_NPT(temperature,press,tau_temperature,tau_pressure) bind(C, name="do_tinker_setup_NPT")
    
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

  !---------------------------------------------------------------------------------------------------------

  subroutine do_tinker_stochastic_one_step(istep) bind(C, name="do_tinker_stochastic_one_step")

    implicit none
    
    integer(kind=c_int32_t) :: istep
    
    call sdstep(istep,dt)
  
  end subroutine
  
  !---------------------------------------------------------------------------------------------------------
  
  subroutine do_tinker_stochastic_n_steps(istep,n) bind(C, name="do_tinker_stochastic_n_steps")

    implicit none
    
    integer(kind=c_int32_t) :: istep, n
    
    integer(kind=c_int32_t) :: i
    
    do i=1,n
      istep = istep + 1 
      call sdstep(istep,dt)
    end do
  
  end subroutine
  
  !---------------------------------------------------------------------------------------------------------
  
  
end module
