#ifndef TASK1_H
#define TASK1_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024
#define NUM_THREADS 2



// Simple Thread argument, pass index of S1 and count to be updated
typedef struct
{
    int startIndex;
    int endIndex;

} STARG;



// Global Vars
pthread_mutex_t mutextotal;         // Create a mutex to lock the total
FILE *fp;                           // points to file for readft1()
char *s1,*s2;                       // strings being read from file
int total = 0;                      // total # of s2 found in s1
int n1,n2;                          // length of strings





// Forward Declarations
int num_substring(void*);
int readft1(FILE*);
void task1();
void thread_manager();














// fn:          num_substring
// desc:        THREADED IMPLEMENTATION
//              find a substring within instr.
// Inputs:
//  char* instr:     string to search within
//  char* substr:    substring to find
//  int l_subst:     length of substr
//  int ndx:         index of instr to start at
// Return:
//  0:      substring not found
//  1:      substring found
int num_substring(void * inIndices)
{
    // recover values from input to thread
    STARG* indices = (STARG*) inIndices;
    int startIndex = indices->startIndex;
    int endIndex = indices->endIndex;


    // Loop through indices taken by input
    // To compare s2 to a portion of s1 use strncmp.  Need a portion of s1 to do
    // that.  Use strncpy to take a portion of s1.
    // Lock total, update total, unlock total to protect from other thread.
    // Print a message saying that
    int i=startIndex;
    for(i;i<=endIndex;i++){


        char tmp[3];
        strncpy(tmp,(s1+i),2);
        tmp[2] = '\0';


        pthread_mutex_lock(&mutextotal);
        // total += x;
        strncmp(tmp,s2,2) == 0 ?  total++:0;
        //printf("At s1[%d] of strncmp(%s,%s,2) == 0? %d\n",i,tmp,s2,strncmp(tmp,s2,2)==0);
        //printf("From [%d] total is:%d\n",i,total);
        pthread_mutex_unlock(&mutextotal);

    }// end for(i;i<=endIndex;i++)

    //printf("Finished with indices[%d,%d]\n",startIndex,endIndex);


    pthread_exit((void*) 0);
}// end num_substring










// read a file in
// return -1 if failed
int readft1(FILE *fp)
{
	if((fp=fopen("project-2_code/strings.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s2==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1)-1;  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
}// end readft1










// fn:      task1
// desc:    Call functions to run task1
void task1(){

    readft1(fp);      // read in the string file
    //printf("s1:%ss2:%s",s1,s2);
    //printf("|s1|=%d\n|s2|=%d\n",n1,n2);



   // Create thread manager to call threads on indices
   thread_manager();

   // Print the total
   printf("Total substring count=%d\n",total);


   /* Last thing that main() should do */
   pthread_mutex_destroy(&mutextotal);
}// end task1










// fn:      thread_manager
// desc:    Manage threads to find substring s2 within s1.
//          use NUM_THREADS threads to check whether s2 is in s1
void thread_manager()
{
    int i;                      // number of times the substring occurs,
                                // counters for while and for loops
    int rc;                     // thread checkvar
    void *status;               // thread status



    // Setup threads and mutex
    pthread_t threads[NUM_THREADS];
    printf("created %d threads\n",NUM_THREADS);
    pthread_attr_t attr;
    pthread_mutex_init(&mutextotal, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);





    // Structs containing start and end indices for each thread
    STARG sections[NUM_THREADS];
    sections[0].startIndex = 0;
    sections[0].endIndex = n1/2;
    sections[1].startIndex = n1/2+1;
    sections[1].endIndex = n1;




    /*
        Call num_substring() requires the START and END indices in s1.  Two
        thread implementation.
        Check that threads created successfully
    */
    for(i=0;i<NUM_THREADS;i++) {
      /* Each thread works on a different set of data.
       * The offset is specified by 'i'. The size of
       * the data for each thread is indicated by VECLEN.
       */
       rc = pthread_create(&threads[i], &attr, num_substring, (void *) &sections[i] );
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
   }// end for(i=0;i<NUMTHRDS;i++)




   // Destroy thread attributes object
   pthread_attr_destroy(&attr);

   /* Wait on the other threads */
   for(i=0;i<NUM_THREADS;i++){pthread_join(threads[i], &status);}



}// end thread_manager


#endif TASK2_H
