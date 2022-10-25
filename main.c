/*    Mini Project 2
      Derrik Pollock
          CMPS 4103
    ******************
    This program creates 5 threads using 
    a global variable. Each thread accesses an array
    initialized with 10,000 elements of array[i] % 257
    Each thread will calculate the running total off all 
    the indexes up until that thread ends.
    Once all threads are exited, the grand TOTAL is printed.
    - Using semaphores: Prevented the threads from running in different
    order each time I ran the program. Instead each thread was made to wait until 
    the previous thread exited. This made the total constant instead of varying on 
    each execution of the program.
    *********************************
    */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 5
#define arrSize 10000
int ARRAY[arrSize];
int TOTAL = 0;

// Init Semaphore
pthread_mutex_t mutex;

//
void *ArraySum(void *tid) {
  // init thread count to thread id 
  int thread_num = *(int *)tid;
  // beginning point 
  int x = (thread_num - 1) * 2000;
  // ending point
  int n = thread_num * 2000 - 1;
 
  for (x; x <= n; x++) {
    // lock mutex buffer
    pthread_mutex_lock(&mutex);
    TOTAL = TOTAL + ARRAY[x];
    // unlock buffer
    pthread_mutex_unlock(&mutex);
  }
  printf(" Total in Thread %d: %d\n", thread_num ,TOTAL);
  // exit function after thread finishes
  pthread_exit(NULL);
  // free memory allocation to avoid garbage in thread identifier
  free(tid);
}
// main //
int main(int argc, char *argv[]) {
  int j, i;
  // initial 5 threads
  pthread_t threads[NUMBER_OF_THREADS];

  // clear memory allocation
  pthread_mutex_init(&mutex, 0);

  /* Initialize array */
  for (i = 0; i < arrSize; i++) {
    ARRAY[i] = i % 257;
    // printf("Value at ARRAY[%d]: %d\n", k, ARRAY[k]);
  }

  for (i = 1; i <= NUMBER_OF_THREADS; i++) {
    // memory allocation to 
    int* threadNum = malloc(sizeof(int));
    *threadNum = i;
    // printf("threadnum %d\n", *threadNum);
    pthread_create(&threads[i], NULL, ArraySum, (int*)threadNum);
  }
  // join all threads with pthread join
  for (i = 1; i <= NUMBER_OF_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  // after all threads have exited and been joined, print total sum of array index values
  printf("\nThe Total after all threads finish is: %d\n", TOTAL);
  return (0);
}
