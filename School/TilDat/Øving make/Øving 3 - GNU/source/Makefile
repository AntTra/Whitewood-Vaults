.PHONY: clean
clean : 
	rm -f *.o
.DEFAULT_GOAL := taco

CC := gcc

CFLAGS := -O0 -g3 

tacoDependencies = taco_krydder.o taco_saus.o taco_lefse.o protein.o grønnsaker.o drikke.o main.o


taco : $(tacoDependencies)
	$(CC) $(CFLAGS) $(tacoDependencies) -o $@



