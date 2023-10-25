# Comando para compilar
# make clean all

SRCDIR = $(CURDIR)/src
BINDIR = $(CURDIR)/bin

INC_LGRAPHS = $(CURDIR)/lgraphs/include
LIB_LGRAPHS = $(CURDIR)/lgraphs/lib

INC_MGRAPHS = $(CURDIR)/mgraphs/include
LIB_MGRAPHS = $(CURDIR)/mgraphs/lib

APP = $(SRCDIR)/app.c
APP_LGRAPHS = $(SRCDIR)/app_lgraphs.c
APP_MGRAPHS = $(SRCDIR)/app_mgraphs.c

all: compileapps

#Create library and bin folders
createfolders: clean
	mkdir -p $(BINDIR)

#Compile tests
compilelibrarys: createfolders
	cd lgraphs && make all
	cd mgraphs && make all

compileapps: compilelibrarys
	gcc $(APP) -o $(BINDIR)/app.out 
	gcc $(APP_LGRAPHS) -llgraphs -lm -o $(BINDIR)/app_lgraphs.out -L $(LIB_LGRAPHS)
	gcc $(APP_MGRAPHS) -lmgraphs -o $(BINDIR)/app_mgraphs.out -L $(LIB_MGRAPHS)

clean:
	cd lgraphs && make clean
	cd mgraphs && make clean
	rm -rf $(BINDIR)
