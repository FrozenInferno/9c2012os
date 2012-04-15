#include "tempExtractn.h"
#include "command.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int ExtractTemp()
{
  FILE *tempTmp;
  char tmp[10] = "",final[10] ="",exec[30];
  int i,j;
  
  system("nvclock -i | grep temperature | tail -c 5 | head -c 3 > temp.tmp ; sleep 1");	//extracting the load from the device
  
  tempTmp = fopen("temp.tmp","a+");
  
  if(tempTmp == NULL)
  {
    printf("Error: Cannot access temporary files..");
    exit(0);
  }
  
  fread(tmp,sizeof(char),9,tempTmp);
  //printf("temp = %s \n",tmp);

  for( i = j = 0 ; i < 9 ; i++ )
  {
    if(tmp[i] == 'C')
      final[j++] = '\0';
    
    if(isdigit(tmp[i]) || tmp[i] == '.' || tmp[i] == '\0')
      final[j++] = tmp[i];
  }
  final[j++] = '\0';

  sprintf(exec,"echo \"%s\" >> TempLog.dat",final);
  
    
  system(exec);
  
  system("rm temp.tmp");
  fclose(tempTmp);
  return atoi(final);
}


void logTemperature()
{
  FILE *TempLog;
  char exec[1000];
  
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
    sprintf(exec,"cat TempLog.dat | tail -n %d > TpLog.dat && rm TempLog.dat && mv TpLog.dat TempLog.dat",NoOfTempRecords);
    
    system(exec);					//Trim the log file to size
    
}


// int main()
// {
//    logTemperature();
//    return 0;
// }
