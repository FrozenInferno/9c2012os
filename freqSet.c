#include "freqSet.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>

float ExtractMemClk()
{
  FILE *tempFile;
  char tempChar1[10],tempChar2[4];
  int i,j;

  system("nvidia-smi -q| grep Memory | tail -n 1 > temp.dat");	//extracting the memory clock speed

  tempFile = fopen("temp.dat","r");

  if(tempFile == NULL)
  {
    printf("Error: Cannot access Temporary files..");
    fclose(tempFile);
    exit(0);
  }

  if(fread(tempChar1,sizeof(tempChar1),1,tempFile) == 0)
  {
    printf("Error: failed to record the data..");
    fclose(tempFile);
    exit(0);
  }
  
  for(i = 0, j = 0; i < strlen(tempChar1) ; i++ )	//extract only the digits and ignore the unit and whitespaces(C)
  {
    if(isdigit(tempChar1[i]) || tempChar1[i] == '.')
      tempChar2[j++] = tempChar1[i];
  }

  tempChar2[j]='\0';					//terminate the string

  fclose(tempFile);
  system("rm temp.dat");
  return(atof(tempChar2));

}

float ExtractCoreClk()
{
  FILE *tempFile;
  char tempChar1[10],tempChar2[4];
  int i,j;

  system("nvidia-smi -q| grep SM | tail -n 1> temp.dat");	//extracting the Stream Multiprocessor clock speed

  tempFile = fopen("temp.dat","r");

  if(tempFile == NULL)
  {
    printf("Error: Cannot access Temporary files..");
    fclose(tempFile);
    exit(0);
  }

  if(fread(tempChar1,sizeof(tempChar1),1,tempFile) == 0)
  {
    printf("Error: failed to record the data..");
    fclose(tempFile);
    exit(0);
  }
  
  for(i = 0, j = 0; i < sizeof(tempChar1) ; i++ )	//extract only the digits and ignore the unit and whitespaces(C)
  {
    if(isdigit(tempChar1[i]) || tempChar1[i] == '.')
      tempChar2[j++] = tempChar1[i];
  }

  tempChar2[j]='\0';					//terminate the string

  fclose(tempFile);
  system("rm temp.dat");
  return(atof(tempChar2));

}


void setFreq(int SMFreq, int memFreq)
{
  char cmd[1000];
  sprintf(cmd,"nvclock -n %d -m %d",SMFreq,memFreq);
  system(cmd);
}

void logFreq(int SMFreq, int memFreq)
{
  FILE *CoreLog, *MemLog;
  char cmd[1000];
  float coreClk,memClk;
  int i;
  
  setFreq(SMFreq,memFreq);
  
  for(i = 0 ; i < 3 ; i++)
  {
  CoreLog = fopen("CoreLog.dat","a+");
  MemLog = fopen("MemLog.dat","a+");
  
  if(MemLog == NULL || CoreLog == NULL)
  {
    printf("Error: Cannot access Log files..");
    exit(0);
  }

    coreClk = ExtractCoreClk();
    memClk = ExtractMemClk();
    fprintf(CoreLog,"%f\n",coreClk);	//write the current load into the log file
    fprintf(MemLog,"%f\n",memClk);	//write the current power into the log file
    
    fclose(MemLog);
    fclose(CoreLog);
    
    sprintf(cmd,"cat CoreLog.dat | tail -n %d > CreLog.dat && rm CoreLog.dat && mv CreLog.dat CoreLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
    
    sprintf(cmd,"cat MemLog.dat | tail -n %d > MmLog.dat && rm MemLog.dat && mv MmLog.dat MemLog.dat",NoOfTempRecords);
    system(cmd);					//Trim th.date log file to sizeof
    
    sleep(10);
  }
  system("nvclock -r");	//reset to the default values.. This is only for testing purposes and must be removed later..
  
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