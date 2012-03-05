#include "tempExtractn.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


float ExtractTemp()
{
  system("nvidia-smi -q| grep Gpu | tail -c 6 | head -c 3 >> TempLog.dat");	//extracting the temperature
  system("nvidia-smi -q| grep Fan | tail -c 4 | head -c 2 >> FanSpeedLog.dat");	//extracting the fan speed
}


void logTemperature()
{
  FILE *TempLog;
  char cmd[1000];
  
  TempLog = fopen("TempLog.dat","a+");
  
  if(TempLog == NULL)
  {
    printf("Error: Cannot access Load files..");
    exit(0);
  }
    ExtractTemp();
    fprintf(TempLog,"\n");	//write the current temperature into the log file
    fflush(TempLog);
    fclose(TempLog);
    sprintf(cmd,"cat TempLog.dat | tail -n %d > TpLog.dat && rm TempLog.dat && mv TpLog.dat TempLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
    
}


// int main()
// {
//    logTemperature();
//    return 0;
// }