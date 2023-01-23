# Makefile compilacao programa
# Para efetuar a compilação digite make all
# Para remover os arquivos temporários digite make clean
# Para remover os arquivos temporários e o arquivo executável digite make purge

CFLAGS = -Wall -g

MODULOS = binary-tree \
	error-handle \
	list \
	generate-message

OBJETOS = main.o $(addsuffix .o,$(MODULOS)) 

.PHONY : all clean

all : teste

teste : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)

purge: 
	$(RM) $(OBJETOS) teste
