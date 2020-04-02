# Project 2

## Task 1
Given two character strings `s1` and `s2`. Write a `Pthread` program to find out the number of substrings, in string `s1`, that is exactly the same as `s2`. For example, if number `substring(s1,
s2)` implements the function, then you have number `substring(‘‘abcdab", ‘‘ab") = 2`,
number `substring(‘‘aaa", ‘‘a") = 3`, and number `substring(‘‘abac", ‘‘bc") = 0`.
The size of `s1` and `s2` (`n1` and `n2`), as well as their data are the input by the user, via a file.
Assume that `n1` is at least twice as long as `n2`.
Attached code substring `sequential.c` is a sequential solution of the problem. `read_f()`
reads the two strings from a file named `string.txt`, and `num_substring()` calculates the
number of substrings. Write a parallel program using `Pthread` based on this sequential
solution.

## Task 2
Use _**condition variables**_ to solve a producer-consumer problem. Here we have two threads: one producer and one consumer. The producer reads characters one by one from a string stored in a file named `message.txt`, then writes sequentially these characters into a circular queue. Meanwhile, the consumer reads sequentially from the queue and prints them in the
same order. Assume a buffer (queue) size of 6 characters. Write a `Pthread` program using
condition variables.

## Task 3
Find the implementation of Task 3 in [task3/](https://github.com/Andreas237/CS5500_OS_Project2/blob/master/task3).
Read attached code `list-forming.c` and modify the program to improve its performance.
In this program there are `num_threads` threads. Each thread creates a data node and
attaches it to a global list. This operation is repeated `K` times by each thread. The performance of this program is measured by the program runtime (in microsecond). Apparently,
the operation of attaching a node to the global list needs to be protected by a lock and the
time to acquire the lock contributes to the total run time. Try to modify the program in
order to reduce the program runtime.

### Task 3 Requirements
1. Implement a modified version of `list-forming.c` and name it `my_list-forming.c`.
2. Verify that your program achieves better performance than the original version by
using different combinations of `K` and num_threads. Typical values of `K` could be `200,
400, 800,...` Typical values of num threads could be `2, 4, 8, 16, 32, 64,...` Draw
diagrams to show the performance trend.
3. In the report, explain your design and discuss the performance results.



## Implementation Details


### Tasks **1** and **2**  
Are each implemented in their own `.h` files.  `main.c` runs  both.

T


To compile on a GNU/Linux machine type `make` in the root directors.
 - `.o` files are generated in `odir/`
 - `.h` files are in `include/`


`make clean` removes `.o` files `*~` `core` and the executable, `exec_p2`


### Task **3**
Is implemented on its own because due to the requirements in **project2.pdf**.  See `task3/`, a `Makefile` is provided for simplicity.  In order to generate results for plotting a `bash` script it provided.  The data is written to `task3/data.txt` ([thanks!](https://www.cyberciti.biz/faq/bash-script-output/)).  Python's `matplotlib` will graph the results.
