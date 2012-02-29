#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define NoOfTempRecords 1000

float ExtractLoad()
{
  FILE *tempFile;
  char tempChar1[10],tempChar2[4];
  int i,j;

  system("nvidia-smi -q| grep Gpu |head -n 1 > tempLoad.dat");	//extracting the load

  tempFile = fopen("tempLoad.dat","r");

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
  system("rm tempLoad.dat > /dev/null 2>&1");
  return(atof(tempChar2));

}


float ExtractCurrentPowerDraw()
{
  FILE *tempFile;
  char tempChar1[10],tempChar2[4];
  int i,j;

  system("nvidia-smi -q| grep \"Power Draw\" > tempPowerDrw.dat");	//extracting the power drawn

  tempFile = fopen("tempPowerDrw.dat","r");

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
  system("rm tempPowerDrw.dat > /dev/null 2>&1");
  return(atof(tempChar2));

}



int main()
{
  FILE *LoadLog, *PowerLog;
  char cmd[1000];
  float curLoad,curPower;
  int i;
  

  system("rm LoadLog.dat > dev/null 2>&1");
  system("rm PowerLog.dat > dev/null 2>&1");
  
  LoadLog = fopen("LoadLog.dat","a+");
  PowerLog = fopen("PowerLog.dat","a+");
  
  if(LoadLog == NULL || PowerLog == NULL)
  {
    printf("Error: Cannot access Log files..");
    exit(0);
  }

    curLoad = ExtractLoad();
    curPower = ExtractCurrentPowerDraw();
    fprintf(LoadLog,"%f\n",curLoad);	//write the current load into the log file
    fprintf(PowerLog,"%f\n",curPower);	//write the current power into the log file
    
    fclose(LoadLog);
    fclose(PowerLog);
    
    sprintf(cmd,"cat LoadLog.dat | tail -n %d > LoadLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
    
    sprintf(cmd,"cat PowerLog.dat | tail -n %d > PowerLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to sizeof
  
  return(0);
}