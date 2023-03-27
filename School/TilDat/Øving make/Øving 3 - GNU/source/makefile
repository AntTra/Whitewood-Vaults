.PHONY: clean
clean :
		rm -f *.o

main.o : main.c 
	gcc -c main.c -o main.o


taco : ost.o lefse.o saus.o protein.o
	gcc -o taco ost.o lefse.o saus.o protein.o

ost.o : ost.c
	gcc -c ost.c

lefse.o : lefse.c
	gcc -c lefse.c

saus.o : saus.c
	gcc -c saus.c

protein.o : protein.c
	gcc -c protein.

.DEFAULT_GOAL := production

debug : main.c
	gcc main.c -00 -g3

production : main.c
	gcc main.c -03

OBJ = ost.o lefse.o saus.o protein.o

taco : $(OBJ)
	gcc -o taco $(OBJ)

LEFSE = $(MEL)
MEL = $(KORN)
KORN = "karbohydrater"
default:
	echo $(LEFSE)

X := "sjokolade"
Y := "$(X)kake"
X := "gulrotkake"

define LINES =
"Linje en"
$(LINJE_TO)
endef

OBJ = ost.o lefse.o saus.o protein.o tacokrydder.o\
	avokado.o rømme.o bønner.o nachos.o mais.o\
	paprika.o løk.o olje.o

OBJ = ost.o lefse.o saus.o protein.o
taco : $(OBJ)
	gcc -o taco $(OBJ)

$(OBJ) : råvare_pris.h


