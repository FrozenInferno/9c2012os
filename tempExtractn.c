#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define NoOfTempRecords 1000

float ExtractTemp()
{
  FILE *tempFile;
  char tempChar1[10],tempChar2[4];
  int i,j;

  system("nvidia-smi -q| grep Gpu | tail -n 1 > temp.dat");	//extracting the temperature

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


int main()
{
  FILE *TempLog;
  char cmd[1000];
  int i;
  float curTemp;

  system("rm TempLog.dat > dev/null 2>&1");

  TempLog = fopen("TempLog.dat","a+");
  
  if(TempLog == NULL)
  {
    printf("Error: Cannot access Load files..");
    exit(0);
  }

    curTemp = ExtractTemp();
    fprintf(TempLog,"%f\n",curTemp);	//write the current temperature into the log file
    
    fclose(TempLog);
    sprintf(cmd,"cat TempLog.dat | tail -n %d > TempLog.dat",NoOfTempRecords);
    system(cmd);					//Trim the log file to size
  
  return(0);
}