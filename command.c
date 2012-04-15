#include "command.h"
#include <ctype.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

float ExecuteCmd(char command[])
{
  FILE *CmdTmp;
  char tmp[100],final[10],pid[7];
  int Usage;
  int i,j;
  
  strcat(command," > cmd.tmp");
  system(command);
  
  CmdTmp = fopen("cmd.tmp","r+");
  
  if(CmdTmp == NULL)
  {
    printf("Error: Cannot access temporary files..");
    exit(0);
  }
  
  fread(tmp,sizeof(char),99,CmdTmp); 

  for( i = j = 0 ; i < 99 ; i++ )
    if(isdigit(tmp[i]) || tmp[i] == '.' )
      final[j++] = tmp[i];
    else if(tmp[i] == '\n' || tmp[i] == '\0')
    {
      final[j++] = '\0';
      break;
    }

  final[j] == '\0';
    
      
  fclose(CmdTmp);
  system("rm cmd.tmp");
 
  return atof(final);
}
