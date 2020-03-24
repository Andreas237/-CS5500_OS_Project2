#ifndef TASK2_H
#define TASK2_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 6


// Global vars
char BUFF[BUFF_SIZE];       // six character buffer required by the project spec
pthread_mutex_t BUFF_TRACKER[BUFF_SIZE];       // six character buffer required by the project spec
char fname[] = "project-2_code/message.txt";
FILE *fp;           // pointer for file
int CONTINUE = 1;





// fn:      consumer
// desc:    Read one character from BUFF.  Write it to the buffer, wraparound
//          when the end of the buffer is reached
void consumer(void){
    char c;
    char * consumer_ptr = BUFF;
    int index = 0;

    do{
        printf("CONSUMER: Removing %c in BUFF[%d]\n",consumer_ptr[index],index);
        consumer_ptr[index] = (char *)0;    // clear current
        index = (index+1) % BUFF_SIZE;      // next space
        if( consumer_ptr[index] != (char *)0){




        }// end if
    // }while(consumer_ptr[index] != (char *)0 );
}while(CONTINUE);


    // Cleanup
    // pthread_exit((void*) 0);
}// end void consumer(void)





// fn:      producer
// desc:    Read one character from *fp.  Write it to the buffer, wraparound
//          when the end of the buffer is reached
void producer(void){
    char c;
    char * producer_ptr = BUFF;
    int index = 0;



    do{
        c = getc(fp);
        if( producer_ptr[index] == (char *)0 && producer_ptr[index] != EOF){
            producer_ptr[index] = c;
            printf("PRODUCER: Placing %c in BUFF[%d]\n",producer_ptr[index],index);
            index = (index+1) % BUFF_SIZE;
        }// end if
    }while( !feof(fp));


    // Cleanup
    CONTINUE = 0;           // end the
    //pthread_exit((void*) 0);
}// end producer





// fn:      readft2
// desc:    Open the file for reading.
int readft2(){

    if((fp=fopen(fname, "r"))==NULL){
		printf("ERROR: can't open %s! Exiting.\n",fname);
		return 0;
	}
}// end readft2







// fn:      task2
// desc:    Call functions to run task1
void task2(){

    // Setup the file pointer, open the file
    if(!readft2()){ exit(1);}

    // Write null chars to the buffer
    int i;
    for(i=0; i<BUFF_SIZE; i++)
        BUFF[i] = (char *)0;

    // Setup threads
    pthread_t threads[2];
    int rc;


    //TODO: How to thread these?  attributes?
    /*
    printf("In task2: creating threads PRODCUER\n");
    rc = pthread_create(&threads[t], NULL, producer, (void *));
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }// end if (rc)
    rc = 0;         // reset


    printf("In task2: creating threads CONSUMER\n");
    rc = pthread_create(&threads[t], NULL, producer, (void *));
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }// end if (rc)
    rc = 0;         // reset
    */

    /*
    producer();
    consumer();
    */

    // Cleanup file stream
    fclose(fp);


}// end task2





#endif TASK2
