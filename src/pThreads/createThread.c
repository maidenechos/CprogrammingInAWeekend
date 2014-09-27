#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void *printHello(void *threadId)
{
  long tid;
  tid = (long)threadId;
  printf("[AniB]: printHello() threadID #%ld\n",tid);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;

  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("In main: creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
    if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
    }
  }
  /* Last thing that main() should do */
  pthread_exit(NULL);
  return 0;
}
