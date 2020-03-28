#include "task1.h"
#include "task2.h"
//#include "task3.h"


void prettyPrintBegin(int);
void prettyPrintEnd(int);



// thread_manager is the runner function
int main(void){

   prettyPrintBegin(1);
   task1();
   prettyPrintEnd(1);






   prettyPrintBegin(2);
   task2();
   prettyPrintEnd(2);






   prettyPrintBegin(3);
   // task3();
   prettyPrintEnd(3);



   pthread_exit(NULL);

   return 0;

}// end main









// Format print for CLI
void prettyPrintBegin(int taskNo){
    printf("\n=========================\n");
    printf("\tTask %d\n",taskNo);
    printf("-------------------------\n");
}// end prettyPrintBegin









// Format print for CLI
void prettyPrintEnd(int taskNo){
    printf("\n\n\tEnd Task %d\n",taskNo);
    printf("-------------------------\n");
    printf("=========================\n\n\n");
}// end prettyPrintBegin
