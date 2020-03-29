/*
  list-forming.c:
  Each thread generates a data node, attaches it to a global list. This is reapeated for K times.
  There are num_threads threads. The value of "num_threads" is input by the student.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sched.h>

// #define K 200 // genreate a data node for K times in each thread


// Forward declarations
//---------------------
void bind_thread_to_cpu(int);
struct Node* generate_data_node();
void * producer_thread( void *);
void * producer_thread_a(void *);
int run_assignment(int,int);





// Struct definitions
//-------------------
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
//---------------------





// Global Vars
//-------------------
pthread_mutex_t    mutex_lock;  // mutex lock variable
struct list *List;              // global list of nodes
int K = 200;                    // K value per assignment, default is 200












int main(int argc, char* argv[])
{
    int i, num_threads;

    int NUM_PROCS;//number of CPU
    int* cpu_array = NULL;

    struct Node  *tmp,*next;
    struct timeval starttime, endtime;

    if(argc == 1){
        printf("ERROR: please provide an input arg (the number of threads)\n");
        exit(1);
    }


    if(argc < 3){
        printf("No K value provided in argv[2], using default of %d\n",K);
    }
    else{
      K = atoi(argv[2]);
    }



    num_threads = atoi(argv[1]); //read num_threads from user
    pthread_t producer[num_threads];
    NUM_PROCS = sysconf(_SC_NPROCESSORS_CONF);//get number of CPU
    if( NUM_PROCS > 0)
    {
        cpu_array = (int *)malloc(NUM_PROCS*sizeof(int));
        if( cpu_array == NULL )
        {
            printf("Allocation failed!\n");
            exit(0);
        }
        else
        {
            for( i = 0; i < NUM_PROCS; i++)
               cpu_array[i] = i;
        }

    }


    // For report
    printf("|Number or processors: %d|\t|Number of threads (inputted): %d|\t",NUM_PROCS,num_threads);


    pthread_mutex_init(&mutex_lock, NULL);

    List = (struct list *)malloc(sizeof(struct list));
    if( NULL == List )
    {
       printf("End here\n");
       exit(0);
    }
    List->header = List->tail = NULL;

    gettimeofday(&starttime,NULL); //get program start time
    for( i = 0; i < num_threads; i++ )
    {
        pthread_create(&(producer[i]), NULL, (void *) producer_thread, &cpu_array[i%NUM_PROCS]);
    }

    for( i = 0; i < num_threads; i++ )
    {
        if(producer[i] != 0)
        {
            pthread_join(producer[i],NULL);
        }
    }


    gettimeofday(&endtime,NULL); //get the finish time

    if( List->header != NULL )
    {
        next = tmp = List->header;
        while( tmp != NULL )
        {
           next = tmp->next;
           free(tmp);
           tmp = next;
        }
    }
    if( cpu_array!= NULL)
       free(cpu_array);


    /* calculate program runtime */
    //printf("Total run time is %ld microseconds.\n", (endtime.tv_sec-starttime.tv_sec) * 1000000+(endtime.tv_usec-starttime.tv_usec));
    printf("|Initial run time (microseconds): %ld|\t", (endtime.tv_sec-starttime.tv_sec) * 1000000+(endtime.tv_usec-starttime.tv_usec));




    return 0 * run_assignment(NUM_PROCS,num_threads);
}// end int main(int argc, char const *argv[]) {








void bind_thread_to_cpu(int cpuid) {
       cpu_set_t mask;
       CPU_ZERO(&mask);

       CPU_SET(cpuid, &mask);
       if (sched_setaffinity(0, sizeof(cpu_set_t), &mask)) {
           fprintf(stderr, "sched_setaffinity");
           exit(EXIT_FAILURE);
       }
  }








struct Node* generate_data_node(){
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
              while(1){
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
            }//end while(1)
        }// end if( NULL != ptr )

        ++counter;

    }// end while( counter  < K )

}// end void * producer_thread( void *arg)









void * producer_thread_a( void * arg){

      int* thread_no = (int*)arg;
      bind_thread_to_cpu(*(thread_no));//bind this thread to a CPU

      struct Node * ptr, tmp;
      struct list * local;
      local = (struct list *)malloc(sizeof(struct list));
      local->header = local->tail = NULL;
      int counter = 0;

      // setup the start of the local list
      local->header = local->tail = generate_data_node();
      local->header->data = local->tail->data = 1;
      // printf("Created the head/tail of the local list\n");

      /* generate and attach K nodes */
      while( counter  < K ){
          // create a node
          ptr = generate_data_node();
          ptr->data  = 1; //generate data

          // add it to the end of the local list
          local->tail->next = ptr;
          local->tail = ptr;

          // increment count for number of data nodes to generate
          ++counter;

      }// end while( counter  < K )

    // printf("Created %d nodes on local list for thread[%d]\n",counter,thread_no);


    /* Attach the local list of nodes to the global list */
    while(1){
        /* access the critical region and add a node to the global list */
        if( !pthread_mutex_trylock(&mutex_lock) )
        {

          // Copied from producer_thread()
          /* attache the generated node to the global list */
          if( List->header == NULL )
          {
              List->header = List->tail = local->header;
          }
          else
          {
              List->tail->next = ptr;
              List->tail = ptr;
          }

          /*  Me adding my list in
                List->tail->next = local->header;
                List->tail = local->tail;
          */
          pthread_mutex_unlock(&mutex_lock);
          // print debug like an expert
          //printf("Added  %d nodes on local list for thread[%d] to the global list\n",counter,thread_no);
          break;
      }// end if( !pthread_mutex_trylock(&mutex_lock) )
      //printf("Failed to obtain lock in thread[%ls]\n",thread_no);

    }//end while(1)



}// end void * producer_thread_a( void *)








/**
  \fn run_assignment
  \var void* arg Thread number from main
  \return int 0 if successful, 1 if not
*/
int run_assignment(int NUM_PROCS, int num_threads){

  int i;

  int* cpu_array = NULL;

  struct Node  *tmp,*next;
  struct timeval starttime, endtime;



  pthread_t producer[num_threads];


  NUM_PROCS = sysconf(_SC_NPROCESSORS_CONF);//get number of CPU
  if( NUM_PROCS > 0)
  {
      cpu_array = (int *)malloc(NUM_PROCS*sizeof(int));
      if( cpu_array == NULL )
      {
          printf("Allocation failed!\n");
          exit(0);
      }
      else
      {
          for( i = 0; i < NUM_PROCS; i++)
             cpu_array[i] = i;
      }

  }





  // For report
  //printf("Number or processors: %d\nNumber of threads (inputted): %d\n",NUM_PROCS,num_threads);


  pthread_mutex_init(&mutex_lock, NULL);



  List = (struct list *)malloc(sizeof(struct list));
  if( NULL == List )
  {
     printf("End here\n");
     exit(0);
  }


  List->header = List->tail = NULL;
  //printf("Created the list in run_assignment()\n");

  gettimeofday(&starttime,NULL); //get program start time
  for( i = 0; i < num_threads; i++ )
  {
      pthread_create(&(producer[i]), NULL, (void *) producer_thread_a, &cpu_array[i%NUM_PROCS]);
  }
  //printf("Created %d threads in run_assignment()\n",i);


  for( i = 0; i < num_threads; i++ )
  {
      if(producer[i] != 0)
      {
          pthread_join(producer[i],NULL);
      }
  }


  gettimeofday(&endtime,NULL); //get the finish time

  if( List->header != NULL )
  {
      next = tmp = List->header;
      while( tmp != NULL )
      {
         next = tmp->next;
         free(tmp);
         tmp = next;
      }
  }
  if( cpu_array!= NULL)
     free(cpu_array);
  /* calculate program runtime */
  // printf("Total run time for our implementation is %ld microseconds.\n", (endtime.tv_sec-starttime.tv_sec) * 1000000+(endtime.tv_usec-starttime.tv_usec));
  printf("|Modified run time (microseconds): %ld|\t", (endtime.tv_sec-starttime.tv_sec) * 1000000+(endtime.tv_usec-starttime.tv_usec));
  return 0;
}// end void run_assignment(int NUM_PROCS, int num_threads)
