#include "governor.h"

void setFreq(int percent)
{
switch(percent)
	{
	case 33: printf("GPU RUNNING AT 33%\n"); break;
	case 50: printf("GPU RUNNING AT 50%\n"); break;
	case 75: printf("GPU RUNNING AT 75%\n"); break;
	case 100: printf("GPU RUNNING AT 100%\n"); break;
	}
}

void onDemand()
{
printf("GPU is AutoScaling Mode\n");
}

void powerSaver()
{
printf("GPU is in PowerSaver Mode\n");
}
