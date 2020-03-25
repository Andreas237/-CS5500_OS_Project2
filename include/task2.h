#ifndef TASK2_H
#define TASK2_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 6
#define NUM_THREAD 2


// Global vars
pthread_mutex_t mutex_buff; // Create a mutex to lock the total
char BUFF[BUFF_SIZE];       // six character buffer required by the project spec
char fname[] = "project-2_code/message.txt";
FILE *fp;           // pointer for file





// fn:      consumer
// desc:    Read one character from BUFF.  Write it to the buffer, wraparound
//          when the end of the buffer is reached
void consumer(void){
    char * consumer_ptr = BUFF;
    int index = 0;
    printf("CONSUMER: not empty-  %c in BUFF[%d]\n",consumer_ptr[index],index);

    //  CONTINUE indicates that characters are still being read from *fp.
    //  Read characters until producer() signals with CONTINUE that the file is
    //  empty.
    do{
        //  Print the next char, overwrite with null, increment index
        if( consumer_ptr[index] != (char *)0){

            // Do the updates only if the lock is available
            if( pthread_mutex_trylock(&mutex_buff) ){

            printf("CONSUMER: Removing %c in BUFF[%d]\n",consumer_ptr[index],index);
            consumer_ptr[index] = (char *)0;    // clear current buffer space
            index = (index+1) % BUFF_SIZE;      // next buffer space
            pthread_mutex_unlock(&mutex_buff);  // Cede control of critical reg.
            }// end if( pthread_mutex_trylock(&mutex_buff) )

        }// end if( consumer_ptr[index] != (char *)0)
        else {
            printf("CONSUMER: not empty-  %c in BUFF[%d]\n",consumer_ptr[index],index);
        }

    }while( !feof(fp) );


    // Cleanup
    pthread_exit((void*) 0);
}// end void consumer(void)





// fn:      producer
// desc:    Read one character from *fp.  Write it to the buffer, wraparound
//          when the end of the buffer is reached
void producer(void){
    char c;
    char * producer_ptr = BUFF;
    int index = 0;



    //  Read the file while there are more characters
    while( !feof(fp) ){

        if( producer_ptr[index] == (char *)0 ){

            if( pthread_mutex_trylock(&mutex_buff) ){
                producer_ptr[index] = getc(fp);;
                printf("PRODUCER: Placing %c in BUFF[%d]\n",producer_ptr[index],index);
                index = (index+1) % BUFF_SIZE;
                pthread_mutex_unlock(&mutex_buff);  // Cede control of critical region

            }// end if( pthread_mutex_trylock(&mutex_buff) )

        }// end if if( producer_ptr[index] == (char *)0
        else{
            printf("PRODUCER: not empty-  %c in BUFF[%d]\n",producer_ptr[index],index);
        }

    }// end while( !feof(fp) )


    // Cleanup
    if( !fclose(fp) ){ printf("Failed to close the file.\n"); }
    pthread_exit((void*) 0);
}// end producer





// fn:      readft2
// desc:    Open the file for reading.
int readft2(){

    if((fp=fopen(fname, "r"))==NULL){
		printf("ERROR: can't open %s! Exiting.\n",fname);
		return 0;
	}
    return 1;
}// end readft2







// fn:      task2
// desc:    Call functions to run task1
void task2(){

    pthread_t threads[NUM_THREAD];          // unique IDs for threads
    int rc;                                 // return code for pthread_create
    void *status;                           // status for terminated thread
    pthread_attr_t attr;                    // pthread attribute
    pthread_attr_init(&attr);               // initialize the attribute
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);    // make attr joinable


    // Setup the file pointer, open the file
    if(!readft2()){ exit(1);}

    // Write null chars to the buffer
    int i;
    for(i=0; i<BUFF_SIZE; i++)
        BUFF[i] = (char *)0;

    // Setup threads



    // Make them joinable


    //TODO: How to thread these?  attributes?
    //TODO: Lec7 discusses semaphores and mutexes; Lec8 pthread

    printf("In task2: creating threads PRODCUER\n");
    rc = pthread_create(&threads[0], &attr, producer, (void *)0);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }// end if (rc)
    rc = 0;         // reset


    printf("In task2: creating threads CONSUMER\n");
    rc = pthread_create(&threads[1], &attr, producer, (void *)0);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }// end if (rc)
    rc = 0;         // reset


    for(i=0; i<NUM_THREAD;i++)
        pthread_join(threads[i], &status);

    // Cleanup
    pthread_mutex_destroy(&mutex_buff);



}// end task2





#endif
