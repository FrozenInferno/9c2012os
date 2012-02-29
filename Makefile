wap: loadExtractn.c tempExtractn.c freqSet.c master.c
	gcc -o loadExtractn loadExtractn.c
	gcc -o tempExtractn tempExtractn.c
	gcc -o freqSet freqSet.c
	gcc -o master master.c -lpthread