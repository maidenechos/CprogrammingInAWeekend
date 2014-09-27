#include<stdio.h>
#include<pthread.h>
pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

int flag=0;
void *EVEN(void *param);
void *ODD(void *param);

int main()
{
  pthread_t etid,otid;
  pthread_create(&etid,NULL,EVEN,NULL);
  pthread_create(&otid,NULL,ODD,NULL);
  pthread_exit(NULL);
}

void *EVEN(void *param)
{
  int x=0;
  int i;
  for(i=0;i<20;i++)
  {
    pthread_mutex_lock(&mlock);
    if(flag==1)
      pthread_cond_wait(&cond,&mlock);
    printf("%d ",x);
    x=x+2;
    flag=1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mlock);
  }
}

void *ODD(void *param)
{
  int x=1;
  int i;
  for(i=0;i<20;i++)
  {
    pthread_mutex_lock(&mlock);
    if(flag==0)
      pthread_cond_wait(&cond,&mlock);
    printf("%d ",x);
    x=x+2;
    flag=0;
    pthread_mutex_unlock(&mlock);
    pthread_cond_signal(&cond);
  }
}
