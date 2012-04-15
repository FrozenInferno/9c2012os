#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "freqSet.h"
#include "loadExtractn.h"
#include "tempExtractn.h"

extern void logLoad();
extern void logTemperature();

int buffer[5];
int flag = 0,autoflag = 1, staticFreq = 75;

int temperature;

int curFreq,nxtFreq;
float curLoad = 0,trigLoad = 67;


void *tmpThread()
{
  logTemperature();
}

void *utilThread()
{
  logLoad();
}

void UIDisplay(int heat, int util, int speed)
{
 FILE* fp;
 fp =fopen("display.txt","w+");
 if(fp == NULL)
   {
     if(flag == 0)
       {
         printf("\nThe display console could not be accessed..\n");
	 flag = 1;
       }
   }
 else
  {
   if(util >= 90)
    { 
     if(autoflag == 0 && staticFreq != 100)
       fprintf(fp,"GPU Overloaded.\nSwitch to higher level\n\tor auto.",util,heat,speed);
     else
       fprintf(fp,"GPU Load : %d %%\nTemperature : %d C\nFrequency: %d MHz",util,heat,speed);
    }
   else
    fprintf(fp,"GPU Load : %d %%\nTemperature : %d C\nFrequency: %d MHz",util,heat,speed);

    fclose(fp);
  }
}

void governingAlgorithm()
{
  FILE *loadTmp;
  char tmp[10];
  int i,j;


  last5load(buffer);
  
  if(buffer[4] > buffer [3] &&buffer[3] > buffer [2] && buffer[2] > buffer [1] && buffer[1] > buffer [0] && trigLoad > 50)
    trigLoad = trigLoad - 5;
  else if(buffer[4] < buffer [3] &&buffer[3] < buffer [2] && buffer[2] < buffer [1] && buffer[1] < buffer [0] && trigLoad < 90)
    trigLoad = trigLoad + 5;
  else	//to restore the value once the load stabilize 
    trigLoad = 67;	//67 being the frequency being aimed for lying between 60 and 75

  if(curLoad < 60 || curLoad > 75 )
  {
    nxtFreq = curLoad * curFreq/trigLoad;
  }
 
  if(nxtFreq == curFreq)
  {
    if(curLoad < 60 && curFreq > 150)
    {
      nxtFreq = nxtFreq - 25;
    }
    if(curLoad > 75 && curFreq < 350 )
    {
      nxtFreq = nxtFreq + 25;
    }
  }

  if(temperature > 87)
    nxtFreq = curFreq - 50;


  fflush(stdout);
  setFreq(nxtFreq);

}

void UIController()
{
   FILE* fp;
   char input[100];
 fp =fopen("log.txt","r");
 if(fp == NULL)
   {
     if(flag == 0)
       {
         printf("\nThe display console could not be accessed..\n");
	 flag = 1;
       }
   }
 else
  {
    fscanf(fp,"%s",input);
    if(strncmp(input,"mode:1") == 0)
      autoflag = 1;
    else
      autoflag = 0;

   fscanf(fp,"%s",input);
   if(strncmp(input,"frequency:33") == 0) staticFreq = 33;
   if(strncmp(input,"frequency:50") == 0) staticFreq = 50;
   if(strncmp(input,"frequency:75") == 0) staticFreq = 75;
   if(strncmp(input,"frequency:100") == 0) staticFreq = 100;

    fclose(fp);
  }
}


int main()
{
  pthread_t temperatureThread,utilizationThread;
    
  init();
  system("./button&");

  for(;;)
  {
//  pthread_create(&temperatureThread,NULL,tmpThread,NULL);
//  pthread_create(&utilizationThread,NULL,utilThread,NULL);
  
//  pthread_join(temperatureThread,NULL);
//  pthread_join(utilizationThread,NULL);
   UIController();
   
  curFreq = nxtFreq = extractCurrentFrequency();
 
  curLoad = ExtractLoad(curFreq);

  temperature = ExtractTemp();

   if(autoflag == 1)
   governingAlgorithm();
   
   else
   {
     if(temperature > 87)
     {
       nxtFreq = curFreq - 50;
       setFreq(nxtFreq);
     }
     else
     setFreq(100 + staticFreq * 250 / 100);
   }

    UIDisplay(temperature,curLoad,curFreq);
    printf("%d\t%d\t%f\t%d\n",curFreq, nxtFreq,curLoad,temperature);


  sleep(1);
  }
  system("killall button");
  return 0;
}
