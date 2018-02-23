all:
	g++ -fopenmp -O3 -march=native -c main.cpp
	
	gfortran -fopenmp -O3 -march=native -fintrinsic-modules-path=$(HOME)/bin/tinker/mods -c fortran_interface.f95
	
# 	g++ -fopenmp -O3 -march=native *.o $(HOME)/bin/tinker/libtinker.a -o tinker_cpp_itf -lgfortran -lfftw3 -lfftw3_threads
	
	g++ -fopenmp -O3 -march=native *.o -o tinker_cpp_itf -L$(HOME)/bin/tinker -Wl,-rpath,$(HOME)/bin/tinker \
	-ltinker -lgfortran -lfftw3 -lfftw3_threads


clean:
	rm -f *.o tinker_cpp_itf
