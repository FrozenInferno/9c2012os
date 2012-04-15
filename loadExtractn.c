#include "loadExtractn.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int loadMax[12];

void init()
{
   int i=0,j;
   printf("\nInitializing..\n");
loadMax[0]=3800;
loadMax[1]=5400;
loadMax[2]=6000;
loadMax[3]=6800;
loadMax[4]=7500;
loadMax[5]=8200;
loadMax[6]=8800;
loadMax[7]=9400;
loadMax[8]=9900;
loadMax[9]=10400;
loadMax[10] = 10900;
printf("\nDone initializing...\n");
}


int maxLoad( int max[], int curFreq)
{
 int lvl;
 int min = curFreq;
 
 if(min > curFreq - 100)
{
   lvl = 0;
   min = curFreq  -100; 
}
 
if(min > curFreq - 125)
{
   lvl = 1;
   min = curFreq  -125; 
}

if(min > curFreq - 150)
{
   lvl = 2;
   min = curFreq  -150; 
}

if(min > curFreq - 175)
{
   lvl = 3;
   min = curFreq  -175; 
}

if(min > curFreq - 200)
{
   lvl = 4;
   min = curFreq  -200; 
}

if(min > curFreq - 225)
{
   lvl = 5;
   min = curFreq  -225; 
}

if(min > curFreq - 250)
{
   lvl = 6;
   min = curFreq  - 250; 
}

if(min > curFreq - 275)
{
   lvl = 7;
   min = curFreq  - 275; 
}

if(min > curFreq - 300)
{
   lvl = 8;
   min = curFreq  - 300; 
}

if(min > curFreq - 325)
{
   lvl = 9;
   min = curFreq  -325; 
}

if(min > curFreq - 350)
{
   lvl = 10;
   min = curFreq  - 350; 
}

return max[lvl];

}

int ExtractLoad(int curFreq)
{
  FILE *loadTmp;
  char tmp[10] = "",final[10] = "",exec[300],pid[7],numberOfProc = 0;
  int usage = 0;
  int i,j,val;
  
  system("./glxgears > load.tmp");
  
  loadTmp = fopen("load.tmp","r+");
  
  if(loadTmp == NULL)
  {
    printf("Error: Cannot access temporary files..");
    exit(0);
  }

  fread(tmp,sizeof(char),9,loadTmp);
  
  for( i = j = 0 ; i < 9 ; i++ )
  {
    if( tmp[i] == '.' )
    {
      final[j++] = '\0';
      break;
    }

    if(isdigit(tmp[i]) || tmp[i] == '\0')
      final[j++] = tmp[i];
  }

  final[j] = '\0';
  val = atoi(final);
  system("rm load.tmp");
  fclose(loadTmp);

  val = val * 100;

  val = val / (float) maxLoad( loadMax, curFreq);

  val = 100 - val;

  if (val < 0)
   val = 0;

  if(val > 100)
    val = 100;

    logLoad(val);

  return val;
}

int getLoad()
{
  FILE *loadTmp;
  char tmp[10] = "",final[10] = "",exec[300],pid[7],numberOfProc = 0;
  int usage = 0;
  int i,j;
  
  system("tail -n 1 LoadLog.dat > getload.tmp");
  
  loadTmp = fopen("getload.tmp","r+");
  
  if(loadTmp == NULL)
  {
    printf("Error: Cannot access temporary files..");
    exit(0);
  }

  fread(tmp,sizeof(char),9,loadTmp);
  
  for( i = j = 0 ; i < 9 ; i++ )
  {
    if( tmp[i] == '.' )
      final[j++] = '\0';

    if(isdigit(tmp[i]) || tmp[i] == '\0')
      final[j++] = tmp[i];
  }  

  final[j] = '\0';
  system("rm load.tmp");
  fclose(loadTmp);
  return atoi(final);
}

void logLoad(int curLoad)
{
  char exec[1000];
  FILE *LoadLog;
  LoadLog = fopen("LoadLog.dat","a+");
  
  if(LoadLog == NULL)
  {
    printf("Error: Cannot access Log files..");
    exit(0);
  }
    sprintf(exec,"echo \"%d\" >> LoadLog.dat",curLoad);
    system(exec);
    //fprintf(LoadLog,"\n");	//write the current load into the log file
    
    
    fclose(LoadLog);
    
    sprintf(exec,"cat LoadLog.dat | tail -n %d > LdLog.dat && rm LoadLog.dat && mv LdLog.dat LoadLog.dat",NoOfTempRecords);
    system(exec);					//Trim the log file to size
 
}

void last5load(int* buffer){
FILE *LoadLog;
char tmp[10];
int i,j;
  LoadLog = fopen("LoadLog.dat","r");
  
  if(LoadLog == NULL)
  {
    printf("Error: Cannot access Log files..");
    exit(0);
  }

for(i = 0 ; i < 5 ; i++)
{
fscanf(LoadLog,"%s",tmp);
for(j=0;j<10;j++)
if(tmp[j] == '\n')
{
tmp[j] = '\0';
break;
}

buffer[i] = atoi(tmp);
}
fclose(LoadLog);
}

// int main()
// {
//   logLoad();
//   return 0;
// }
