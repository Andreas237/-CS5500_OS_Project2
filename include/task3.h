#ifndef TASK3_H
#define TASK3_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sched.h>

#define K 200 // genreate a data node for K times in each thread

struct Node
{
    int data;
    struct Node* next;
};

struct list
{
     struct Node * header;
     struct Node * tail;
};

pthread_mutex_t    mutex_lock;

struct list *List;

void bind_thread_to_cpu(int cpuid) {
     cpu_set_t mask;
     CPU_ZERO(&mask);

     CPU_SET(cpuid, &mask);
     if (sched_setaffinity(0, sizeof(cpu_set_t), &mask)) {
         fprintf(stderr, "sched_setaffinity");
         exit(EXIT_FAILURE);
     }
}

struct Node* generate_data_node()
{
    struct Node *ptr;
    ptr = (struct Node *)malloc(sizeof(struct Node));

    if( NULL != ptr ){
        ptr->next = NULL;
    }
    else {
        printf("Node allocation failed!\n");
    }
    return ptr;
}

void * producer_thread( void *arg)
{
    bind_thread_to_cpu(*((int*)arg));//bind this thread to a CPU

    struct Node * ptr, tmp;
    int counter = 0;

    /* generate and attach K nodes to the global list */
    while( counter  < K )
    {
        ptr = generate_data_node();

        if( NULL != ptr )
        {
            while(1)
            {
		/* access the critical region and add a node to the global list */
                if( !pthread_mutex_trylock(&mutex_lock) )
                {
                    ptr->data  = 1;//generate data
		    /* attache the generated node to the global list */
                    if( List->header == NULL )
                    {
                        List->header = List->tail = ptr;
                    }
                    else
                    {
                        List->tail->next = ptr;
                        List->tail = ptr;
                    }
                    pthread_mutex_unlock(&mutex_lock);
                    break;
                }
            }
        }
        ++counter;
    }
}










// fn:      task3
// desc:    Call functions to run task1
float task3(){
    clock_t t;



    // Cleanup


    // Finish clock
    float runtime_seconds = clock() - t;
    return runtime_seconds;
}// end task3








#endif
