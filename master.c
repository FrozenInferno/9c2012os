#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "freqSet.h"
#include "loadExtractn.h"
#include "tempExtractn.h"

extern void logLoad();
extern void logTemperature();

void *tmpThread()
{
  logTemperature();
}

void *utilThread()
{
  logLoad();
}

int main()
{
  int i;
  pthread_t temperatureThread,utilizationThread;
  
  for(i = 0 ; i < 120 ; i++)
  {
  pthread_create(&temperatureThread,NULL,tmpThread,NULL);
  pthread_create(&utilizationThread,NULL,utilThread,NULL);
  
  pthread_join(temperatureThread,NULL);
  pthread_join(utilizationThread,NULL);
  
  sleep(1);
  }
  return 0;
}