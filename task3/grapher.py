#!/usr/bin/env python3

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import csv



# Create a bar chart with K-values on the y-axis, and number_of_threads on the
# x-axis.  Each bar should be topped with the runtime.  The bars should be
# colored based on whether they are modified, or generic implementations.
def grapher():
    labels = ['G1', 'G2', 'G3', 'G4', 'G5']
    men_means = [20, 34, 30, 35, 27]
    women_means = [25, 32, 34, 20, 25]

    x = np.arange(len(labels))  # the label locations
    width = 0.35  # the width of the bars

    fig, ax = plt.subplots()
    rects1 = ax.bar(x - width/2, men_means, width, label='Men')
    rects2 = ax.bar(x + width/2, women_means, width, label='Women')

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('Scores')
    ax.set_title('Scores by group and gender')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()


    def autolabel(rects):
        """Attach a text label above each bar in *rects*, displaying its height."""
        for rect in rects:
            height = rect.get_height()
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')


    autolabel(rects1)
    autolabel(rects2)

    fig.tight_layout()

    plt.show()



# Create a bar chart with K-values on the y-axis, and number_of_threads on the
# x-axis.  Each bar should be topped with the runtime.  The bars should be
# colored based on whether they are modified, or generic implementations.
def grapher(num_threads,k_vals,generic_time,modified_time):
    labels = num_threads

    x = np.arange(len(labels))  # the label locations
    width = 0.35  # the width of the bars

    fig, ax = plt.subplots()
    rects1 = ax.bar(x - width/2, generic_time, width, label='Generic')
    rects2 = ax.bar(x + width/2, modified_time, width, label='Modified')

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('K-values')
    ax.set_title('Runtime by Implementation')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()


    def autolabel(rects):
        """Attach a text label above each bar in *rects*, displaying its height."""
        for rect in rects:
            height = rect.get_height()
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')


    autolabel(rects1)
    autolabel(rects2)

    fig.tight_layout()

    plt.show()






# Read the data from the file.  Discard useless stuff, the rest is read into
# arrays for summarizing
# Data format:
# [Number of Processors;Number of Threads;K-Value;Generic Runtime (microseconds);Modified Runtime(microseconds);Which is faster]
def runner():
    print("In runner")

    num_proc = []
    num_threads = []
    k_vals = []
    generic_time = []
    modified_time = []


    # open file,
    with open('data.txt') as fin:

        found_start = 0

        for line in fin:
            if("begin_data" in line):
                found_start = 1
                continue
            if( found_start):
                tokens = line.split(';')
                # num_proc.append(tokens[0])    # Always the same
                num_threads.append(tokens[1])

                k_vals.append(tokens[2])
                generic_time.append(tokens[3])
                modified_time.append(tokens[4])




    fin.close()

    # grapher()
    # num_threads = list(dict.fromkeys(num_threads))
    grapher(num_threads,k_vals,generic_time,modified_time)
    print("num_threads: ",num_threads)
    print("exit(0)")
