


CC 			=  clang
CFLAGS 		= -ggdb -Wall -std=gnu99
FFLAGS		= 
DEPS		= 

all:  runner

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(FFLAGS) -c  $< -o $@


OBJS=	circular-buffer.o	\
		runner.o

runner: $(OBJS)
	$(CC) $(CFLAGS) $(FFLAGS) -o $@ $(OBJS)

clean:
	-rm *.o 
	-rm runner
