all: speaker anagrammer

speaker: speaker.c wordlist.h wordlist.o
	gcc -Wall -o speaker speaker.c wordlist.o

anagrammer: anagrammer.c anagramlist.h anagramlist.o
	gcc -Wall -o anagrammer anagrammer.c anagramlist.o

anagramlist.o: anagramlist.h
wordlist.o: wordlist.h

clean:
	rm -f speaker.o wordlist.o anagrammer.o anagramlist.o speaker anagrammer a.out
