/*
 * Code injection trick for Tinker 8.4
 * 
 * By preloading the random.so library obtained when compiling this file we can redefine the random_ and normal_ function below.
 * 
 * this way we can control precisely the random generator, for example making sure that different replicas  running in parallel will be initialized with different random seeds.
 * 
 * Note that this only works when linking to dynamic version of Tinker, e.g. a libtinker.so
 * 
 * LD_PRELOAD=/home/hedin/prog/tinker_cpp_itf/random.so ./tinker_cpp_itf 
 * 
 */

#include <random>
#include <array>
// #include <limits>
// #include <iostream>

// the only things visible from outside of the following function

extern "C"
{
  double random_();
  double normal_();
}

// ------------------------------------------------------------
// This is internal to this file

using namespace std;

// this is the random numbers generator
static mt19937 generator;

// this distribution generates a real random number uniformly distributed between 0 and 1
static uniform_real_distribution<double>  double_0_1_unif(0.0,1.0);

// this distribution generates a real random number normally distributed between 0 and 1
static normal_distribution<double>  double_0_1_norm(0.0,1.0);

static bool first_call = true;

//------------------------------------------------------------
// implementation of C/Fortran interfaces

static void init_rand()
{
  // hardware random number generator used for creating initial seeds : on linux it is mapped to /dev/random or /dev/urandom
  random_device rd;
  
  /*
   * read 512 uint64_t 'seeds' from random_device, one after each other
   */
  array<uint64_t,512> seeds;
  for(size_t n=0; n<512; n++)
    seeds[n] = rd();
  
//   cout << "Seeds : " << '\t';
//   for(auto& seed : seeds)
//     cout << seed << '\t';
//   cout << endl;

  // initialise the mt19937 with the seed sequence
  seed_seq seq(seeds.begin(),seeds.end());
  generator.seed(seq);
  
  // finally discard some random numbers to be sure to avoid any correlation
  generator.discard(4*generator.state_size);
  
  first_call = false;
  
}

double random_()
{
//   cout << "Hello from the c++ override of random_() !! " << endl;
  
  if(first_call)
    init_rand();
  
  return double_0_1_unif(generator);
}

double normal_()
{
//     cout << "Hello from the c++ override of normal_() !! " << endl;
  
  if(first_call)
    init_rand();
  
  return double_0_1_norm(generator);
}
