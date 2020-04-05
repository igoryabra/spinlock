clang++ *.cpp -emit-llvm -c
llvm-link tests.bc spinlock.bc -S -o project.ll
genmc -randomize-schedule project.ll
