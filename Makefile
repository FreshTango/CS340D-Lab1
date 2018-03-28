mygrep :
	gcc *.c -o mygrep
all :
	gcc *.c -o mygrep
clean:
	-rm -f mygrep.o
	-rm -f mygrep