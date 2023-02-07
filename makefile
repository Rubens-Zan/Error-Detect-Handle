# Makefile compilacao programa
# Para efetuar a compilação digite make all
# Para remover os arquivos temporários digite make clean
# Para remover os arquivos temporários e o arquivo executável digite make purge
CC     = gcc -g
CFLAGS = -g

PROG = teste
OBJS = binary-tree.o \
	error-handle.o \
	list.o \
	generate-message.o


.PHONY:  clean purge all debug

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS) $(PROG).o
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -DDEBUG
debug: $(PROG)

clean:
	@rm -f *~ *.bak

purge:  clean
	@rm -f *.o core a.out
	@rm -f $(PROG)

