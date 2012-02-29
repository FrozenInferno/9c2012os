#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *tmpThread()
{
  system("./tempExtractn");
}

void *utilThread()
{
  system("./loadExtractn");
}

void main()
{
  int i;
  pthread_t temperatureThread,utilizationThread;
  
  for(i = 0 ; i < 10 ; i++)
  {
  pthread_create(&temperatureThread,NULL,tmpThread,NULL);
  pthread_create(&utilizationThread,NULL,utilThread,NULL);
  
  pthread_join(temperatureThread,NULL);
  pthread_join(utilizationThread,NULL);
  
  sleep(300);
  }
}
