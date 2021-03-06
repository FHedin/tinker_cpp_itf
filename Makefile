CXX  = g++ -std=c++14
FC   = gfortran -std=f2008
OPTS = -O3 -g -march=native -Wall -Wextra

TINKER_HOME = $(HOME)/bin/tinker
TINKER_LIB  = $(TINKER_HOME)/libtinker.so
TINKER_MODS_DIR = $(TINKER_HOME)/mods

EXEC = tinker_cpp_itf
LIBS = -lgfortran -lfftw3 -lfftw3_threads

all:
	@mkdir -p obj
	
	$(CXX) -fopenmp $(OPTS) -c main.cpp -o obj/main.o
	$(FC)  -fopenmp $(OPTS) -fintrinsic-modules-path=$(TINKER_MODS_DIR) -c tinker_interface.f08 -o obj/tinker_interface.o
	$(CXX) -fopenmp $(OPTS) obj/*.o $(TINKER_LIB) -o $(EXEC) $(LIBS) -Wl,-rpath,$(TINKER_HOME)
	
	$(CXX) -shared $(OPTS) -fPIC random.cpp -Wl,-soname,random.so -o random.so

clean:
	rm -f obj/*.o *.so $(EXEC)
