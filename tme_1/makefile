maintab: tab.o maintab.o
		gcc -o maintab tab.o maintab.o
tab.o : tab.c
		gcc -o tab.o -c tab.c -Wall -O

maintab.o: maintab.c tab.h
		gcc -o maintab.o -c maintab.c -Wall -O

clean:
	rm -rf *.o