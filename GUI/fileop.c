#include "fileop.h"
#include <stdio.h>
#include <string.h>

char automatic[] ="mode:1";
char manual[] = "mode:0";
char freq100[]="frequency:100";
char freq75[]="frequency:75";
char freq50[]="frequency:50";
char freq33[]="frequency:33";

int set100(){
FILE *fp;
fp=fopen("log.txt","w+");
fputs(manual,fp);
fputc('\n',fp);
fputs(freq100,fp);
fclose(fp);
return 0;
}

int set75(){
FILE *fp;
fp=fopen("log.txt","w+");
fputs(manual,fp);
fputc('\n',fp);
fputs(freq75,fp);
fclose(fp);
return 0;
}

int set50(){
FILE *fp;
fp=fopen("log.txt","w+");
fputs(manual,fp);
fputc('\n',fp);
fputs(freq50,fp);
fclose(fp);
return 0;
}

int set33(){
FILE *fp;
fp=fopen("log.txt","w+");
fputs(manual,fp);
fputc('\n',fp);
fputs(freq33,fp);
fclose(fp);
return 0;
}

int setAuto(){
FILE *fp;
fp=fopen("log.txt","w+");
fputs(automatic,fp);
fclose(fp);
return 0;
}
