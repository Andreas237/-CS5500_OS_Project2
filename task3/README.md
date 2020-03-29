## Task 3 Write-up
### Task Information
1. See `my_list-forming.c` for the implementation.
  * `void * producer_thread_a( void * arg)` implements our thread producer.  First a local list `local` is created and `K` nodes are appended.  Next the critical region is locked (using `trylock`) and that list is inserted into the global list `List`.
  * `long run_assignment(int NUM_PROCS, int num_threads)` is a slightly modified version of `main`, and called from `main`.  This method returns the runtime of of the program using `producer_thread_a`.
  * `list-forming.c` was modified so that `K` can be passed as a command line argument, this simplified running multiple experiments.  `main` was modified to print `num_threads`, `NUM_PROCS`, `K`, and `generic_runtime` the runtime of the unmodified `producer_thread()`.
2. (Diagram inbound)
3. Implementation Discussion
  1. The generic implementation requires the critical region to be locked everytime a node is created.  For 20 threads creating 200 nodes the critical region is locked `num_thread * K` times.  In our implementation, `producer_thread_a()`, we create `local`, a list of `K` nodes, and then insert that into the global `List`; this requires locking the critical region `num_thread` times.  
  2. We implemented solutions with `pthread_mutex_lock` and `pthread_mutex_trylock`.  `_lock` is a blocking call and thus no other threads were able to access the critical region; whereas `_trylock` is a non-blocking call.  `_trylock` performed significantly better. See `task3/my_list-forming.c` lines 307 through 349 for that code.
  3. Allowing threads to run on all CPUs should speed up performance since threads not waiting on specific CPUs the amount of time they spent waiting was reduced.  In reality we found that performance was decreased.  This must be due to the cost of switching the process running the thread from one CPU to another.
