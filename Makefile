OBJ=caculator

#CFLAGS = -m32

all: clean
	gcc $(CFLAGS) $(OBJ).c -o $(OBJ)

test:
	./$(OBJ) "1+2"
	./$(OBJ) "1+2+(3+4)"

clean:	
	rm -f $(OBJ)
