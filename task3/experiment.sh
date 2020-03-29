#!/usr/bin/env bash

# Make the executable
clear
make clean
make





K_START=200
K_END=6400

NO_THRD_START=2
NO_THRD_END=256






echo "Number of Processors;Number of Threads;K-Value;Generic Runtime (microseconds);Modified Runtime(microseconds);Which is faster?"
echo "begin_data"

# Loop for K values
for (( k=$K_START; k<=$K_END; k=2*k ))
do


  # Loop for thread values
  for (( t=$NO_THRD_START; t<=$NO_THRD_END; t=2*t ))
  do
    ./my_list-forming $t $k

  done  # end for (( t=$NO_THRD_START; t<=$NO_THRD_END; t=2*t ))





done # end for (( k=$K_START; k<=$K_END; k=2*k ))
