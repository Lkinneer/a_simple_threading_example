#include <pthread.h>
#include <stdio.h>

  
  void * hello(void * var) {
    printf("Hello ");
    pthread_exit(0);
  }

  void * world(void * hello_pointer) {
    if (pthread_join(*(pthread_t*)hello_pointer, NULL)) {
    	fprintf(stderr, "Error joining thread from world\n");
    	pthread_exit(0);	
  	}
    printf("world");
    pthread_exit(0);
  }

  void * exclamation(void * world_pointer) {
  	if (pthread_join(*(pthread_t*)world_pointer, NULL)) {
    	fprintf(stderr, "Error joining thread from exclamation\n");
    	pthread_exit(0);	
  	}
    printf("!");
    pthread_exit(0);
  }

int main() {
	int x;
  

  /* this variable is our reference to the second thread */
  pthread_t hello_thread;
  pthread_t world_thread;
  pthread_t exclamation_thread;

  /* create a second thread which executes inc_x(&x) */
  if (pthread_create( &hello_thread, NULL, hello, & x)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }
  if (pthread_create( &world_thread, NULL, world, & hello_thread)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }
  if (pthread_create( &exclamation_thread, NULL, exclamation, & world_thread)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }

  

  /* wait for the last two threads to finish */
  if (pthread_join(exclamation_thread, NULL)) {
    fprintf(stderr, "Error joining exclamation thread from main\n");
    return 2;
  }
  
  printf("\n");

  return 0;

}