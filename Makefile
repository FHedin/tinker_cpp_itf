all:
	g++ -fopenmp -O3 -march=native -c main.cpp
	g++ -fopenmp -O3 -march=native main.o ~/bin/tinker/libtinker.a -o tinker_cpp_itf -lgfortran -lfftw3 -lfftw3_threads
# 	g++ -fopenmp -O3 -march=native main.o -o tinker_cpp_itf -L/home/hedin/bin/tinker -Wl,-rpath,/home/hedin/bin/tinker \
# 	-ltinker -lgfortran -lfftw3 -lfftw3_threads


