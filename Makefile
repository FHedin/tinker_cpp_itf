CXX  = g++
FC   = gfortran
OPTS = -fopenmp -O3 -march=native

TINKER_HOME = $(HOME)/bin/tinker
TINKER_LIB  = $(TINKER_HOME)/libtinker.a
TINKER_MODS_DIR = $(TINKER_HOME)/mods

EXEC = tinker_cpp_itf
LIBS = -lgfortran -lfftw3 -lfftw3_threads

all:
	@mkdir -p obj
	
	$(CXX) $(OPTS) -c main.cpp -o obj/main.o
	
	$(FC)  $(OPTS) -fintrinsic-modules-path=$(TINKER_MODS_DIR) -c tinker_interface.f95 -o obj/tinker_interface.o
	
	$(CXX) $(OPTS) obj/*.o $(TINKER_LIB) -o $(EXEC) $(LIBS)

clean:
	rm -f obj/*.o $(EXEC)
