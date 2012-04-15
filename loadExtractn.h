#ifndef load
#define load

#define NoOfTempRecords 5

int ExtractLoad(int cpuFreq);
void logLoad();
int maxLoad( int max[], int curFreq);
void last5load(int* buffer);

#endif
