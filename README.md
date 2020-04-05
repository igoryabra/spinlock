# Spinlock

## Instructions

### Required packages
	
* Google Test can be installed by `sudo apt install libgtest-dev`
* GenMC can be installed by instructions here - https://github.com/MPI-SWS/genmc
	
### How to compile
1. Run `cmake CMakeLists.txt`
2. Run `make`

### Usage
Typical usage to run tests with google test: `./tests`  
To try to apply GenMC to LLVM Intermediate Representation of a project:`sh genmc_test.sh`

## Project description

## Tests

All tests generate N = 100 threads, that are writing thread number to a list, protected by spinlock. To test spinlock work in the end of execution resulting list is sorted and compared with list, filled by sequence of numbers from 1 to N.

* std_thread_lock_test - generate N std::thread's, test lock function
* std_thread_try_lock_test - generate N std::threads's, test try_lock function by running it in loop untill it will not return true, which means that spinlock was locked by this thread
* omp_lock_test - generate N OpenMP threads, test lock function
* omp_try_lock_test - generate N OpenMP threads, test try_lock function by running it in loop untill it will not return true, which means that spinlock was locked by this thread

## GenMC

genmc_test.sh generate bitcode files from all of the *.cpp files, link them and generate project.ll file with LLVM Intermediate Representation of a project. Then it apply GenMC instrument to the generated intermediate representation with random order of threads. 
