#include "freqSet.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>

int extractCurrentFrequency()
{
    FILE *loadTmp;
  char tmp[10],final[10],cmd[30];
  int i,j,ret;
  
  system("nvclock -i | grep clock |tail -c 12| head -c 7 > current.tmp");	//extracting the clock frequency from the device
  
  loadTmp = fopen("current.tmp","a+");
  
  if(loadTmp == NULL)
  {
    printf("Error: Cannot access temporary files..");
    exit(0);
  }
  
  fread(tmp,sizeof(char),9,loadTmp);
  
  ret = atoi(tmp);
  
  fflush(stdout);
  
  fclose(loadTmp);
  
  return ret;

}

void setFreq(int SMFreq )
{
  char cmd[1000];
  if(SMFreq < 100)
     SMFreq = 100;

  if(SMFreq > 350)
     SMFreq = 350;

    sprintf(cmd,"nvclock -n %d >/dev/null 2>&1",SMFreq);
    system(cmd);

}

void logFreq(int SMFreq)
{
  char cmd[1000];
  float coreClk;
  int i;
  
  setFreq(SMFreq);
  
  for(i = 0 ; i < 3 ; i++)
  {
    
    sprintf(cmd,"cat CoreLog.dat | tail -n %d > CreLog.dat && rm CoreLog.dat && mv CreLog.dat CoreLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
        
    sleep(10);
  }
  
}

// int main(int argc, char **argv)
// {
//     if(argc != 2)
//     {
//       printf("Incorrect data..!!");
//       return 0;
//     }
// 
//   logFreq(atoi(argv[1]),atoi(argv[2]));
//   return 0;
// }
