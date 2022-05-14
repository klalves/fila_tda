SHELL=/bin/sh
CC=gcc
CFLAGS= -O3
NOME=fila

default:	aplicacao

$(NOME).o:	$(NOME).c $(NOME).h $(NOME)_privado.h
	$(CC) $(CFLAGS) -c $(NOME).c -o $(NOME).o

aplicacao:	aplicacao.c  aplicacao.h $(NOME).o
	$(CC) $(CFLAGS) aplicacao.c $(NOME).o -o aplicacao

clean:
	rm -f *.o core a.out *.*~ Makefile~ aplicacao