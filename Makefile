wap: loadExtractn.c tempExtractn.c freqSet.c master.c
	gcc -o loadExtractn.o -c loadExtractn.c
	gcc -o tempExtractn.o -c tempExtractn.c
	gcc -o freqSet.o -c freqSet.c
	gcc -o master.o -c master.c
	gcc -o master tempExtractn.o loadExtractn.o freqSet.o master.o -lpthread