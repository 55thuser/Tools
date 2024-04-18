#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h> // for O_* constants
#include <semaphore.h>

#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {   //Define mutex
  int    queue1;
  int    queue2;
  sem_t  *q1;
  sem_t  *q2;
  sem_t  *mutex;
} ns_mutex_t;

ns_mutex_t lock;
const char* sem_q1 = "/sem_q1";
const char* sem_q2 = "/sem_q2";
const char* sem_mutex = "/sem_mutex";

sem_t *Sem_open(const char *name, int val) {    //function for unlocking semephores
  sem_t *sem = sem_open(name, O_CREAT, S_IRWXU, val);
  if (sem == SEM_FAILED) {
    printf("failed to create a semaphore.\n");
    exit(0);
  }
  return sem;
}

void ns_mutex_init(ns_mutex_t *m) { //function for initializing 2 semephores and a mutex
  m->queue1 = 0;
  m->queue2 = 0;
  m->q1 = Sem_open(sem_q1, 1);
  m->q2 = Sem_open(sem_q2, 0);        //q2 is initialy set with 0
  m->mutex = Sem_open(sem_mutex, 1);
}

void ns_mutex_acquire(ns_mutex_t *m) {
  Sem_wait(m->mutex);   //locks mutex
  m->queue1 ++;         //increments queue1
  //START MARKER 1
  Sem_post(m->mutex);  //unlocks mutex


  Sem_wait(m->q1);      //locks semiphore
  m->queue2 ++;         //increments queue2
  //START MARKER 2
  Sem_wait(m->mutex);   //locks mutex
  m->queue1 --;         //decrements queue1
  //END MARKER 1

  if (m->queue1 == 0) {     
    Sem_post(m->q2);        //unlocks q2 if MARKER 1 has been started as many times as it has ended
  } else {
    Sem_post(m->q1);        //unlocks q1 if theads are in diffrent stages in above code
  }


  Sem_post(m->mutex);       //unlocks mutex
  

  // use the second queue as the barrier
  Sem_wait(m->q2);          //locks q2
  m->queue2 --;             //decrement queue2
  //END MARKER 2
}

//queue2 is unlocked if number of threads that have aquired mutex are even, locks if odd





void ns_mutex_release(ns_mutex_t *m) {      //unlocks q1 if the number of threads that started MARKER 2 is equivelent as the number of threads that ended MARKER 2, otherwise unlock q2
  if (m->queue2 == 0) {
   Sem_post(m->q1); 
  } else {
   Sem_post(m->q2);
  }
}


void *worker(void *arg) {
    ns_mutex_acquire(&lock);        //aquire mutex

    //CRITICAL SECTION

    int thread_id = (int) pthread_self();       //gets ID of thread

    if (thread_id % 3 == 0)                     //if ID is a multiple of 3 sleep for 1s. ||  IN RUNNING every 3 threads, wait 1sec
      sleep(1);

    printf("%d is running...\n", thread_id);    
    printf("%d queue1\n",lock.queue1);
    printf("%d queue2\n",lock.queue2);
    //END CRITICAL SECTION

    ns_mutex_release(&lock);        //release mutex
    return NULL;
}


int main(int argc, char *argv[]) {
    assert(argc == 2);
    int count = atoi(argv[1]);
    pthread_t threads[count];
    ns_mutex_init(&lock);

    int i;
    for (i = 0; i < count; i++ ) {
      Pthread_create(&threads[i], NULL, worker, NULL);      //create threads by number of arg1
    }

    for(int i = 0; i < count; i++) {
      Pthread_join(threads[i], NULL);                       //wait untill all threads complete
    }
    printf("parent: begin\n");
    printf("parent: end\n");
    Sem_close(lock.q1);
    Sem_close(lock.q2);
    Sem_close(lock.mutex);                                  //CLEANUP AND CLOSE
    Sem_unlink(sem_q1);
    Sem_unlink(sem_q2);
    Sem_unlink(sem_mutex);
    
    return 0;
}
