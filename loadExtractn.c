#include "loadExtractn.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void ExtractLoad()
{
  system("nvidia-smi -q| grep Gpu |head -n 1 | tail -c 5 | head -c 3 >> LoadLog.dat");	//extracting the 
}


void logLoad()
{
  char cmd[1000];
  FILE *LoadLog;
  LoadLog = fopen("LoadLog.dat","a+");
  
  if(LoadLog == NULL)
  {
    printf("Error: Cannot access Log files..");
    exit(0);
  }
    ExtractLoad();
    fprintf(LoadLog,"\n");	//write the current load into the log file
    
    
    fclose(LoadLog);
    
    sprintf(cmd,"cat LoadLog.dat | tail -n %d > LdLog.dat && rm LoadLog.dat && mv LdLog.dat LoadLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
 
}

// int main()
// {
//   logLoad();
//   return 0;
// }