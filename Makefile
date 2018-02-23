all:
	g++ -fopenmp -O3 -march=native -c main.cpp
	
	gfortran -fopenmp -O3 -march=native -fintrinsic-modules-path=fortran_mods -c fortran_interface.f95
	
	g++ -fopenmp -O3 -march=native *.o ~/bin/tinker/libtinker.a -o tinker_cpp_itf -lgfortran -lfftw3 -lfftw3_threads
	
# 	g++ -fopenmp -O3 -march=native main.o -o tinker_cpp_itf -L/home/hedin/bin/tinker -Wl,-rpath,/home/hedin/bin/tinker \
# 	-ltinker -lgfortran -lfftw3 -lfftw3_threads


