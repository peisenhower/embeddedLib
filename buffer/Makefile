


CC 			=  clang
CFLAGS 		= -ggdb -Wall -std=gnu99
FFLAGS		= 
DEPS		= 
INC 		= -I../

all:  test

%.o: %.c $(DEPS)
	@echo "CC 	$<"
	@$(CC) $(CFLAGS) $(FFLAGS) $(INC) -c  $< -o $@


OBJS=	circular-buffer.o	\
		runner.o

test: $(OBJS)
	@echo "LD 	$^"
	@$(CC) $(FFLAGS) -o $@ $(OBJS)

clean:
	@echo "Cleaning..."
	@-rm *.o 
	@-rm test
	@echo "Done"



