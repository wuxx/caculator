OBJ=caculator

#CFLAGS = -m32

all:
	gcc $(CFLAGS) $(OBJ).c -o $(OBJ)

clean:	
	rm -f $(OBJ)
