#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cont = PTHREAD_COND_INITIALIZER;
int flag = 0;

void *EVEN(void *param);
void *ODD(void *param);


int main(int argc, char const *argv[])
{


  pthread_t etid,otid;
  pthread_create(&etid, NULL, EVEN, NULL);
  pthread_create(&otid, NULL, ODD, NULL);

  pthread_exit(NULL);
  return 0;
}
void *EVEN(void *param)
{
  int x = 0;
  int i;

  for (i = 0; i < 20; ++i)
  {
    pthread_mutex_lock(&mlock);
    if (flag == 1)
    {
      pthread_cond_wait(&cont, &mlock);
    }
    printf("%d\n", x);
    x += 2;
    flag=1;
    pthread_cond_signal(&cont);
    pthread_mutex_unlock(&mlock);
  }
}

void *ODD(void *param)
{
  int x = 1;
  int i;

  for (i = 0; i < 20; ++i)
  {

    pthread_mutex_lock(&mlock);
    if (flag == 0)
    {
      pthread_cond_wait(&cont, &mlock);
    }
    printf("%d\n", x);
    x += 2;
    flag=0;
    pthread_cond_signal(&cont);
    pthread_mutex_unlock(&mlock);

  }
}
