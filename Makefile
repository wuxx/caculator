OBJ=caculator

#CFLAGS = -m32
.PHONY: clean

all: clean
	gcc $(CFLAGS) $(OBJ).c expr_pc.c -o $(OBJ)

test:
	./$(OBJ) "1+2"
	./$(OBJ) "1+2+(3+4)"
	./$(OBJ) "1+2+(3+4))"

clean:	
	rm -f $(OBJ)
