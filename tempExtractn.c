#include "tempExtractn.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


float ExtractTemp()
{
  system("nvidia-smi -q| grep Gpu | tail -c 6 | head -c 3 >> TempLog.dat");	//extracting the temperature
  system("nvidia-smi -q| grep Fan | tail -c 5 | head -c 2 >> FanSpeedLog.dat");	//extracting the fan speed
}


void logTemperature()
{
  FILE *TempLog,*FanSpdLog;
  char cmd[1000];
  
  TempLog = fopen("TempLog.dat","a+");
  FanSpdLog = fopen("FanSpeedLog.dat","a+");  

  if(TempLog == NULL || FanSpdLog == NULL)
  {
    printf("Error: Cannot access Load files..");
    exit(0);
  }
    ExtractTemp();
    fprintf(TempLog,"\n");	//write the current temperature into the log file
    fprintf(FanSpdLog,"\n");
    fflush(TempLog);
    fflush(FanSpdLog);
    fclose(TempLog);
    fclose(FanSpdLog);
    sprintf(cmd,"cat TempLog.dat | tail -n %d > TpLog.dat && rm TempLog.dat && mv TpLog.dat TempLog.dat",NoOfTempRecords);
    sprintf(cmd,"cat FanSpeedLog.dat | tail -n %d > Fspd.dat && rm FanSpeedLog.dat && mv Fspd.dat FanSpeedLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
    
}


// int main()
// {
//    logTemperature();
//    return 0;
// }
