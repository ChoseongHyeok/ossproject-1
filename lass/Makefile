
OBJS = kwfind.o main.o 
EXEC = kwfind

CFLAGS = -g
LDFLAGS =

CC = gcc
LD = ld

LIBS = 
LIB_INCLUDE = 

#INCLUDE = -isystem . $(LIB_INCLUDE)
	
all: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

clean:
	rm -rf $(OBJS) $(EXEC)
	rm -rf *.bak
	rm -rf *~
	rm -rf *.o
	rm -rf .*.swp
