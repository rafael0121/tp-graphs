# Comando para compilar
# make clean mgraphs


export BINDIR = $(CURDIR)/bin
export INCDIR = $(CURDIR)/include
export SRCDIR = $(CURDIR)/src
export LIBDIR = $(CURDIR)/lib
export TESDIR = $(CURDIR)/test
SRC = $(wildcard $(SRCDIR)/*.c)
TES = $(wildcard $(TESDIR)/*.c)


all: compiletest

#Create library and bin folders
createfolders: clean
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)

#Compile Library
precompilelibrarys: createfolders
	gcc -Wall -c -I $(INCDIR) $(SRC)

#Ar in a static library 
createstaticlibrary: precompilelibrarys 
	ar rcs  $(LIBDIR)/libmgraphs.a $(wildcard $(CURDIR)/*.o)

#Compile tests
compiletest: createstaticlibrary 
	gcc -Wall $(TES) -lmgraphs -lm -o $(BINDIR)/main.out -I $(INCDIR) -L $(LIBDIR) 

clean:
	rm -rf $(BINDIR)
	rm -rf $(LIBDIR)
	rm -rf *.o
	rm -rf *.out
